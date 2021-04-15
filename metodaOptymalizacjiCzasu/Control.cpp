#include "Control.h"

#include <algorithm>
#include <iostream>
#include <math.h>
#include <fstream>
#include "VecOpp.h"
#include <string>

#include <thread>
#include <future>
#include <chrono>
#include <stdlib.h>

using namespace std::chrono_literals;


Control::Control(const ControlObject& controlObject) : controlObject(controlObject)
#if THREAD == 1
, safeTable(controlObject.stateValues)
#endif // THREAD
{
    name = "secondMethodTable";

#if THREAD == 0

    if(controlObject.stateValues.size() == 1)
    {
        std::vector<ControlPoint> value;
        for(size_t i = 0; i < controlObject.stateValues[0].size();i++)
        {
            value.push_back(ControlPoint());
        }
        table.push_back(value);
    }
    else
    {
        unsigned int num = 1;

        for(size_t i = 1; i < controlObject.stateValues.size();i++)
        {
            num*= controlObject.stateValues[i].size();
        }

        std::vector<ControlPoint> value;
        for(size_t i = 0; i < controlObject.stateValues[0].size();i++)
        {
            std::vector<ControlPoint> value;
            value.reserve(num);
            for(size_t j = 0; j < num;j++)
            {
                value.push_back(ControlPoint());
            }
            table.push_back(value);
        }
    }
#endif // THREAD


}

void Control::createTables()
{

    setFinZeroCost();
    //printTables("baze");

    std::cout<<"success alloc"<<std::endl;

    bool finish = false;
    unsigned int localNumOfCountedPoint = 0;
    for(unsigned int counter = 0; !finish ; counter++)
    {
        finish = true;
        globalCounter = counter + 1;


        if(controlObject.stateValues.size() == 1)
        {
            for(size_t i = 0; i < controlObject.stateValues[0].size();i++)
            {
#if THREAD == 0
                auto& cp = table[0][i];
#else
                auto cp = safeTable.get(0,i);
#endif // THREAD
                if(!(cp.getAvaliable()))
                {
                    const auto& x = controlObject.stateValues[0][i];
                    std::vector<double> xC = {x};
                    if(!calculateOptimalControlValue(xC,cp))
                    {
                        finish = false;
                    }
#if THREAD == 1
                    safeTable.set(0,i,cp);
#endif // THREAD
                }
            }
        }
        else
        {

#if THREAD == 0
            unsigned int i = 0;
            for(const auto& x: controlObject.stateValues[0])
            {
                if(!miniTables(i,{x},1,0))
                {
                    finish = false;
                }
                i++;
                std::cout<<"finx0 " << x << std::endl;
            }

#else
            for(unsigned int i = 0; i < controlObject.stateValues[0].size();i++)
            {
                std::vector<std::future<bool>> threads;
                unsigned int j;
                for(j = 0; i < controlObject.stateValues[0].size() && j<12; j++)
                {
                    std::vector<double> xC = {controlObject.stateValues[0][i]};
                    threads.push_back(std::async(std::launch::async, &Control::miniTables, this, i,xC,1,0));
                    i++;
                }
                i--;

                for(unsigned k = 0; k<j && k<threads.size(); k++)
                {
                    //values.push_back(threads[k].get());
                    if(!threads[k].get())
                    {
                        finish = false;
                    }
                    std::cout<< k << " ";
                }
                std::cout<<std::endl<<"finx0 " << i+1 << "/" << controlObject.stateValues[0].size() << std::endl;

            }

#endif // THREAD

        }

        std::cout<<"fin iteration " << counter << std::endl<<std::endl;
        std::cout<<numOfCountedPoint<<"/"<<controlObject.numOfAllPoint<<std::endl;
        std::cout<<(numOfCountedPoint*100.0)/controlObject.numOfAllPoint<<std::endl<<std::endl;
        //printTables(std::to_string(counter));

        if(localNumOfCountedPoint==numOfCountedPoint)
        {
            finish = true;
        }
        else
        {
            localNumOfCountedPoint = numOfCountedPoint;
        }
    }
}

bool Control::miniTables(size_t tinx, const std::vector<double> x, size_t index, unsigned int offset)
{
    if(index == controlObject.stateValues.size())
    {
#if THREAD == 0
        auto& cp = table[tinx][offset];
#else
        auto cp = safeTable.get(tinx,offset);
#endif // THREAD
        if(!(cp.getAvaliable()))
        {
            if(!calculateOptimalControlValue(x,cp))
            {
                return false;
            }
#if THREAD == 1
            safeTable.set(tinx,offset,cp);
#endif // THREAD
            numOfCountedPoint++;
        }
        return true;
        //ControlPoint opt = calculateOptimalControlValue(t,x);
        //return {opt};
    }
    else
    {
        bool success = true;
        unsigned int num = 1;

        for(size_t i = index+1; i < controlObject.stateValues.size();i++)
        {
            num*= controlObject.stateValues[i].size();
        }

        unsigned int i = 0;
        for(const auto& xN: controlObject.stateValues[index])
        {
            std::vector<double> xC = x;
            xC.push_back(xN);
            if(!miniTables(tinx,xC,index+1,offset+i*num))
            {
                success = false;
            }
            i++;
        }
        return success;
    }
}


bool Control::calculateOptimalControlValue(const std::vector<double>& x,ControlPoint& cp)
{
    bool success = false;
    double refDistance = 1e300;
    for(const auto& u: controlObject.controlValues)
    {
        std::vector<double> xNext = controlObject.xNext(x,u,controlObject.timeRes);

        double distance;
        ControlPoint next = findNearestPoint(xNext,distance);
        if(next.getAvaliable())
        {
            auto cost = next.getCost()+1;

            bool isEnd;
            if(cost>globalCounter)
                isEnd = false;
            else
            {
                isEnd = true;
                success = true;
            }


            if(cost<cp.getCost())
            {
                //std::cout<<"wybieram " <<u<<std::endl<<std::endl;
                cp.setValues(u,cost,isEnd);
            }
            else if(cost==cp.getCost())
            {
                //std::cout<<"wybieram!!!!!!!!!!! " <<u<<std::endl<<std::endl;
                //if(fabs(u)<fabs(cp.getU()))
                //{
                //    cp.setValues(u,cost,true);
                //}
                if(distance<refDistance)
                {
                    refDistance = distance;
                    cp.setValues(u,cost,isEnd);
                }
            }

        }

        //VecOpp::print(x);
        //VecOpp::print(xNext);
        //std::cout<<u<<"\t"<<cost<<std::endl;
        //std::cout<<cost<<"\t"<<optimals.getCost()<<std::endl<<std::endl;
        //std::this_thread::sleep_for(3000ms);


    }

    return success;
}

ControlPoint Control::findNearestPoint(const std::vector<double>& xFind)
{
    std::vector<double> coordinates(xFind.size());

    for(unsigned int i = 0; i < coordinates.size(); i++)
    {
        coordinates[i] = findCoordinate(controlObject.stateValues[i],xFind[i]);
    }


    if(xFind.size()==1)
        //return table[0][coordinates[0]];
#if THREAD == 0
        return table[0][coordinates[0]];
#else
        return safeTable.get(0,coordinates[0]);
#endif // THREAD
    else
    {
// uwaga nie testowana !!!!!!!!!!!!!!!!!!!!!!testy byly probne!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int offset = 0;
        int j = 1;
        for(size_t i = controlObject.stateValues.size()-1; i>0;i--)
        {
            offset += coordinates[i]*j;
            j *= controlObject.stateValues[i].size();
        }
        //return table[coordinates[0]][offset];
#if THREAD == 0
        return table[coordinates[0]][offset];
#else
        return safeTable.get(coordinates[0],offset);
#endif // THREAD
    }


}

ControlPoint Control::findNearestPoint(const std::vector<double>& xFind,double& distance)
{
    std::vector<double> coordinates(xFind.size());
    distance = 0;

    for(unsigned int i = 0; i < coordinates.size(); i++)
    {
        coordinates[i] = findCoordinate(controlObject.stateValues[i],xFind[i]);
        distance += pow( (controlObject.stateValues[i][coordinates[i]]-xFind[i]) ,2);
    }


    if(xFind.size()==1)
        //return table[0][coordinates[0]];
#if THREAD == 0
        return table[0][coordinates[0]];
#else
        return safeTable.get(0,coordinates[0]);
#endif // THREAD
    else
    {
// uwaga nie testowana !!!!!!!!!!!!!!!!!!!!!!testy byly probne!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int offset = 0;
        int j = 1;
        for(size_t i = controlObject.stateValues.size()-1; i>0;i--)
        {
            offset += coordinates[i]*j;
            j *= controlObject.stateValues[i].size();
        }
        //return table[coordinates[0]][offset];
#if THREAD == 0
        return table[coordinates[0]][offset];
#else
        return safeTable.get(coordinates[0],offset);
#endif // THREAD
    }


}

void Control::setFinZeroCost()
{
    std::vector<double> coordinates(controlObject.finState.size());

    for(unsigned int i = 0; i < coordinates.size(); i++)
    {
        coordinates[i] = findCoordinate(controlObject.stateValues[i],controlObject.finState[i]);
    }

    if(controlObject.finState.size()==1)
    {
#if THREAD == 0
        table[0][coordinates[0]].setValues(0,0,true);
#else
        ControlPoint cp(0,0,true);
        safeTable.set(0,coordinates[0],cp);
#endif // THREAD
    }
    else
    {
// uwaga nie testowana !!!!!!!!!!!!!!!!!!!!!!testy byly probne!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int offset = 0;
        int j = 1;
        for(size_t i = controlObject.stateValues.size()-1; i>0;i--)
        {
            offset += coordinates[i]*j;
            j *= controlObject.stateValues[i].size();
        }

#if THREAD == 0
        table[coordinates[0]][offset].setValues(0,0,true);
#else
        ControlPoint cp(0,0,true);
        safeTable.set(coordinates[0],offset,cp);
#endif // THREAD
    }
}

int Control::findCoordinate(const std::vector<double>& vec,const double num)
{
    unsigned int i;
    for(i = 0; i < vec.size(); i++)
    {
        //if(num<=vec[i]) break;
        if(vec[i]>=num) break;
    }

    if(i == 0)
        return 0;
    else if(i>vec.size()-1)
        return vec.size()-1;
    else
    {
        const double temp = (vec[i-1] + vec[i])/2.0;
        if(temp>=num) return i-1;
        else return i;
    }
}


void Control::simulate()
{
    std::cout<<"start simulation"<<std::endl;
    std::fstream File;
    //File.open( "C:\\chwilowy\\prog\\simul.txt", std::ios::out );
    File.open( "C:\\chwilowy\\prog\\"+ name + ".txt", std::ios::out );
    if( File.good() == false)
    {
        std::cout<<"blad"<<std::endl;
        //std::cerr << "Error: " << strerror(errno);
        exit(250);
    }

    double uIdDysk=0, uId = 0, uSim = 0;
    float cIdDysk=0, cId = 0, cSim = 0;
    unsigned int j = 0;
    std::vector<double> xIdDysk = controlObject.initState;
    std::vector<double> xId = controlObject.initState;
    std::vector<double> xSim = controlObject.initState;

    std::vector<double> xT(xId.size()),xT2(xId.size()),xT3(xId.size());

    for(unsigned int i = 0; i<=controlObject.tK/controlObject.dt;i++)
    {
        double t = i*controlObject.dt;

        if(t>=j*controlObject.timeRes)
        {
            auto opt= findNearestPoint(xSim);
            uSim = opt.getU();
            cSim = opt.getCost();

            opt= findNearestPoint(xId);
            uId = opt.getU();
            cId = opt.getCost();

            opt= findNearestPoint(xIdDysk);
            uIdDysk = opt.getU();
            cIdDysk = opt.getCost();
            //j++;
        }

        File << t << ';';
        for(const auto& xp:xIdDysk)
            File << xp << ';';
        File << uIdDysk << ';';
        File << cIdDysk << ';';
        for(const auto& xp:xId)
            File << xp << ';';
        File << uId << ';';
        File << cId << ';';
        for(const auto& xp:xSim)
            File << xp << ';';
        File << uSim << ';';
        File << cSim << '\n';

        //
       /* if(t>=j*controlObject.timeRes){
        for(size_t i = 0; i<xId.size(); i++)
            xT[i] = controlObject.stateValues[i][findCoordinate(controlObject.stateValues[i],xId[i])];
            std::vector<double> dxT = controlObject.diff(xT,uId);
        xT2 = VecOpp::add(xT,VecOpp::mult(dxT,controlObject.timeRes));
        for(size_t i = 0; i<xId.size(); i++)
            xT3[i] = controlObject.stateValues[i][findCoordinate(controlObject.stateValues[i],xT2[i])];
        }
        for(const auto& xp:xT)
            File << xp << ';';
        for(const auto& xp:xT2)
            File << xp << ';';
        for(const auto& xp:xT3)
            File << xp << ';';
        File << '\n';
*/
        //

        std::vector<double> dx = controlObject.diff(xSim,uSim);
        xSim = VecOpp::add(xSim,VecOpp::mult(dx,controlObject.dt));

        if(t>=j*controlObject.timeRes)
        {
            dx = controlObject.diff(xId,uId);
            xId = VecOpp::add(xId,VecOpp::mult(dx,controlObject.timeRes));
            dx = controlObject.diff(xIdDysk,uIdDysk);
            xIdDysk = VecOpp::add(xIdDysk,VecOpp::mult(dx,controlObject.timeRes));


            std::vector<double> coordinates(xIdDysk.size());

            for(unsigned int i = 0; i < coordinates.size(); i++)
            {
                coordinates[i] = findCoordinate(controlObject.stateValues[i],xIdDysk[i]);
                xIdDysk[i] = controlObject.stateValues[i][coordinates[i]];
            }

            j++;
        }
    }

    File.close();
}

void Control::showGraf()
{
    std::string str = "python C:\\chwilowy\\prog\\rysuj3.py C:\\chwilowy\\prog\\"+ name + ".txt" + " " + std::to_string((unsigned int)controlObject.finState.size());
    system(str.c_str());
}

void Control::printTables(std::string name) //float binarnie
// zrobic strukture w ktroej jest x0 x1 x2 x3 plus u i c i zapisywac binarnie ca³a t¹ strukture
{
    std::cout<<"print table"<<std::endl;
    std::fstream File;
    File.open( "C:\\chwilowy\\prog\\table"+name+".txt", std::ios::out );
    if( File.good() == false)
    {
        std::cout<<"blad"<<std::endl;
        //std::cerr << "Error: " << strerror(errno);
        exit(250);
    }

    if(controlObject.stateValues.size() == 1)
    {
        for(unsigned int i = 0; i<controlObject.stateValues[0].size(); i++)
        {
            //std::cout<<j<<std::endl;
#if THREAD == 0
            const auto& opt= table[0][i];
#else
            const auto& opt= safeTable.get(0,i);
#endif // THREAD
            File<<controlObject.stateValues[0][i]<<"\tu= "<<opt.getU()<<" c= "<<opt.getCost()<<" f= "<<opt.getAvaliable()<<std::endl;
        }
    }
    else
    {
        for(unsigned int j = 0; j<controlObject.stateValues[0].size();j++)
        {
            const auto& x0 = controlObject.stateValues[0][j];
            std::cout<<j*100.0/controlObject.stateValues[0].size()<<std::endl;

            std::vector<int> counter (controlObject.initState.size()-1,0);
            counter[counter.size()-1] = -1;

#if THREAD == 0
            for(unsigned int k = 0; k<table[j].size();k++)
#else
            for(unsigned int k = 0; k<safeTable.getSize(j);k++)
#endif // THREAD
            {
                //for(int l = 0; l<counter.size();l++)
                for(int l = counter.size()-1; l>=0;l--)
                {
                    if(l==counter.size()-1) counter[l]++;
                    if(counter[l]>=controlObject.stateValues[l+1].size())
                    {
                        counter[l]=0;
                        if(l-1 > -1)
                            counter[l-1]++;
                    }
                }

#if THREAD == 0
                const auto& opt= table[j][k];
#else
                const auto& opt= safeTable.get(j,k);
#endif // THREAD
                File<<x0<<"\t";

                //for(int l = counter.size()-1; l>=0;l--)
                for(int l = 0; l<counter.size();l++)
                {
                    File<<controlObject.stateValues[l+1][counter[l]]<<"\t";
                }

                File<<"u= "<<opt.getU()<<" c= "<<opt.getCost()<<std::endl;
                //File<<opt.info<<std::endl;
            }
        }
    }

    File.close();

}

