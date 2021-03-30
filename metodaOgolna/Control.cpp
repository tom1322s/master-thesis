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

#define THREAD 1
#define RAM 1

Control::Control(const ControlObject& controlObject) : controlObject(controlObject)
{
    name = "simH" + std::to_string((int)controlObject.H[0][0]);
    for(size_t i = 1; i < controlObject.H.size();i++)
        name += "n" + std::to_string((int)controlObject.H[i][i]);

    name += "Q" + std::to_string((int)controlObject.Q[0][0]);
    for(size_t i = 1; i < controlObject.Q.size();i++)
        name += "n" + std::to_string((int)controlObject.Q[i][i]);

    name += "R" + std::to_string((int)(controlObject.R*100)) + "dt" + std::to_string((double)(controlObject.dt*1000));
    name += "dtime" + std::to_string((int)(controlObject.timeRes*1000));
}

void Control::createTables()
{
    int timeLength = (controlObject.tK-controlObject.t0)/controlObject.timeRes;

    for(int i = timeLength-1; i>=0; i--)
    {
        double t = controlObject.t0 + controlObject.timeRes*i;

        std::vector<std::vector<ControlPoint>> values;

        //std::cout<<controlObject.stateValues.size()<<std::endl;
        if(controlObject.stateValues.size() == 1)
        {
            //std::cout<<"zyje"<<std::endl;
            std::vector<ControlPoint> value;
            for(const auto& x: controlObject.stateValues[0])
            {
                std::vector xC = {x};
                ControlPoint opt = calculateOptimalControlValue(t,xC);

                //std::cout<<t<<"\t";
                //VecOpp::print(xC);
                //std::cout<<"u= "<<opt.getU()<<" c= "<<opt.getCost()<<std::endl;
                //std::this_thread::sleep_for(1000ms);

                value.push_back(opt);
            }
            values.push_back(value);
        }
        else
        {
#if THREAD ==0

            for(const auto& x: controlObject.stateValues[0])
            {
                std::vector<ControlPoint> value = createMiniTables(t,{x},1);
                values.push_back(value);
            }

#else

            for(unsigned int i = 0; i < controlObject.stateValues[0].size();i++)
            {
                std::vector<std::future<std::vector<ControlPoint>>> threads;
                unsigned int j;
                for(j = 0; i < controlObject.stateValues[0].size() && j<12; j++)
                {
                    std::vector<double> xC = {controlObject.stateValues[0][i]};
                    threads.push_back(std::async(std::launch::async, &Control::createMiniTables, this, t,xC,1));
                    i++;
                }
                i--;

                for(unsigned k = 0; k<j && k<threads.size(); k++)
                {
                    values.push_back(threads[k].get());
                    std::cout<<"finK " << k << std::endl;
                }
                std::cout<<"finx0 " << i+1 << "/" << controlObject.stateValues[0].size() << std::endl;

            }

#endif // THREAD
        }

        table.insert(table.begin(),values);
        std::cout<<"fint " << t << std::endl;

#if RAM == 1
        if(table.size()>2)
            printTable(t+controlObject.timeRes*2);
#endif // RAM

    }

#if RAM == 1
        printTable(controlObject.t0 + controlObject.timeRes);
        printTable(controlObject.t0);
#endif // RAM
    //std::cout<<"100= " << table.size() << std::endl;
    //std::cout<<"1= " << table[99].size() << std::endl;
    //std::cout<<"w= " << table[99][0].size() << std::endl;

}

std::vector<ControlPoint> Control::createMiniTables(double t,const std::vector<double> x, size_t index)
{
    if(index == controlObject.stateValues.size())
    {
        ControlPoint opt = calculateOptimalControlValue(t,x);
        //std::cout<<t<<"\t";
        //VecOpp::print(x);
        //std::cout<<"u= "<<opt.getU()<<" c= "<<opt.getCost()<<std::endl;
        return {opt};
    }
    else
    {
        std::vector<ControlPoint> values;
        for(const auto& xN: controlObject.stateValues[index])
        {
            std::vector xC = x;
            xC.push_back(xN);
            std::vector<ControlPoint> temp = std::move(createMiniTables(t,xC,index+1));
            values.insert(values.end(),temp.begin(),temp.end());
        }
        return values;
    }
}


ControlPoint Control::calculateOptimalControlValue(double t, const std::vector<double>& x)
{
    ControlPoint optimals(0,1e300);

    for(const auto& u: controlObject.controlValues)
    {
        std::vector<double> xNext = controlObject.xNext(x,t,u,controlObject.timeRes);
        double cost;
        if(table.size()==0)
        {
            cost = controlObject.finCost(xNext,controlObject.finState);
            //std::cout<<"cost = " << cost << "dla u = "<<u<<std::endl;
            //VecOpp::print(x);
            //VecOpp::print(xNext);
            //std::cout<<std::endl<<std::endl;
            //std::this_thread::sleep_for(1s);

            //cost += controlObject.nextCost(controlObject.timeRes,xNext,controlObject.finState);
            cost += controlObject.nextCost(controlObject.timeRes,x,controlObject.finState,u);
            //cost += controlObject.nextCost(controlObject.timeRes,t,xNext,controlObject.finState,u);
        }
        else
        {
            //cost = controlObject.nextCost(controlObject.timeRes,xNext,controlObject.finState);
            cost = controlObject.nextCost(controlObject.timeRes,x,controlObject.finState,u);
            //cost = controlObject.nextCost(controlObject.timeRes,t,xNext,controlObject.finState,u);
            cost += findNearestPoint(xNext).getCost();

           /* if(cost == 0)
            {
                std::cout<<"Dla punktu";
                VecOpp::print(x);
                VecOpp::print(xNext);
                std::cout<<"przy u = " << u <<std::endl;
                std::cout<<findNearestPoint(xNext).info<<std::endl;
                std::this_thread::sleep_for(15s);
            }*/

            //std::cout<<"Dla punktu";
            //VecOpp::print(x);
            //VecOpp::print(xNext);
            //std::cout<<"przy u = " << u <<std::endl;
            //std::cout<<findNearestPoint(xNext).info<<std::endl;
            //std::this_thread::sleep_for(10s);
        }

        //VecOpp::print(x);
        //VecOpp::print(xNext);
        //std::cout<<u<<"\t"<<cost<<std::endl;
        //std::cout<<cost<<"\t"<<optimals.getCost()<<std::endl<<std::endl;
        //std::this_thread::sleep_for(3000ms);

        if(cost<optimals.getCost())
        {
            //std::cout<<"wybieram " <<u<<std::endl<<std::endl;
            optimals.setValues(u,cost);
        }
        else if(cost==optimals.getCost())
        {
            //std::cout<<"wybieram!!!!!!!!!!! " <<u<<std::endl<<std::endl;
            if(fabs(u)<fabs(optimals.getU()))
            {
                optimals.setValues(u,cost);
            }
        }
    }
    //optimals.info = std::to_string((double)x[0])+"  "+std::to_string((double)x[1])+"  "+std::to_string((double)x[2])+"  "+std::to_string((double)x[3]);
    return optimals;
}

ControlPoint Control::findNearestPoint(const std::vector<double>& xFind,const size_t index)
{
    std::vector<double> coordinates(xFind.size());

    for(unsigned int i = 0; i < coordinates.size(); i++)
    {
        coordinates[i] = findCoordinate(controlObject.stateValues[i],xFind[i]);
    }


    //std::cout<<xFind[0]<<" "<<controlObejct.stateValues[0][coordinates[0]]<<std::endl;
    //std::cout<<xFind[1]<<" "<<controlObejct.stateValues[1][coordinates[1]]<<std::endl;
    //std::cout<<xFind[2]<<" "<<controlObejct.stateValues[2][coordinates[2]]<<std::endl;
    //std::cout<<xFind[3]<<" "<<controlObejct.stateValues[3][coordinates[3]]<<std::endl<<std::endl;
    //std::this_thread::sleep_for(1000ms);
    if(xFind.size()==1)
        return table[index][0][coordinates[0]];
    else
    {
// uwaga nie testowana !!!!!!!!!!!!!!!!!!!!!!testy byly probne!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int offset = 0;
        int j = 1;
        for(size_t i = controlObject.stateValues.size()-1; i>0;i--)
        {
            offset += coordinates[i]*j;
            //std::cout<<controlObject.stateValues[i].size()<<std::endl;
            j *= controlObject.stateValues[i].size();
            //std::cout<<j<<std::endl;
            //std::cout<<"offset"<<offset<<std::endl;
        }

        //VecOpp::print(xFind);
        //std::cout<<"Found "<< controlObject.stateValues[0][coordinates[0]] << "\t" << controlObject.stateValues[1][coordinates[1]] << "\t" << controlObject.stateValues[2][coordinates[2]] << "\t" << controlObject.stateValues[3][coordinates[3]]<<std::endl;
        //std::cout<<"offset"<<offset<<std::endl;
        //std::cout<<"READ "<<table[index][coordinates[0]][offset].info<<std::endl<<std::endl;
        //std::this_thread::sleep_for(10s);

        return table[index][coordinates[0]][offset];
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

    double u=0;
    double c=0;
    unsigned int j = 0;
    std::vector<double> x = controlObject.initState;
    unsigned int numOfIteration = ((controlObject.tK-controlObject.t0)/controlObject.dt);
    //for(double t = controlObject.t0; t<= controlObject.tK+0.0001; t+=controlObject.dt)
    for(unsigned int i = 0; i<=numOfIteration;i++)
    {
        double t = controlObject.t0+i*controlObject.dt;
#if RAM == 0
        if(t>=j*controlObject.timeRes+controlObject.t0 && j<table.size())
#else
        if(t>=j*controlObject.timeRes+controlObject.t0 && i<numOfIteration)
#endif
        {
            //std::cout<<i<<std::endl;
            //u = findNearestPoint(x,i).getU();
#if RAM == 0
            auto opt= findNearestPoint(x,j);
#else
            auto opt= findNearestPointFile(x,t);
            //std::cout<<t<<std::endl;
#endif
            u = opt.getU();
            c = opt.getCost();
            j++;
        }

        File << t << ';';
        for(const auto& xp:x)
            File << xp << ';';
        File << u << ';';
        File << c << '\n';

        std::vector<double> dx = controlObject.diff(x,t,u);
        x = VecOpp::add(x,VecOpp::mult(dx,controlObject.dt));
    }

    File.close();
}

void Control::showGraf()
{
    std::string str = "python C:\\chwilowy\\prog\\rysuj2.py C:\\chwilowy\\prog\\"+ name + ".txt" + " " + std::to_string((unsigned int)controlObject.H.size());
    system(str.c_str());
}

void Control::printTables()
{
    std::cout<<"startToPrint"<<std::endl;
    for(unsigned int i = 0; i<table.size(); i++)
    {
        double t = i * controlObject.timeRes;
        std::fstream File;
        File.open( "C:\\chwilowy\\prog\\table"+std::to_string((unsigned int)i)+".txt", std::ios::out );
        if( File.good() == false)
        {
            std::cout<<"blad"<<std::endl;
            //std::cerr << "Error: " << strerror(errno);
            exit(250);
        }
        //std::cout<<controlObject.stateValues[0].size()<<std::endl;
        if(controlObject.stateValues.size() == 1)
        {
            for(unsigned int j = 0; j<controlObject.stateValues[0].size(); j++)
            {
                //std::cout<<j<<std::endl;
                const auto& opt= table[i][0][j];
                File<<t<<"\t"<<controlObject.stateValues[0][j]<<"\tu= "<<opt.getU()<<" c= "<<opt.getCost()<<std::endl;
            }
        }
        else
        {
            for(unsigned int j = 0; j<controlObject.stateValues[0].size();j++)
            {
                const auto& x0 = controlObject.stateValues[0][j];

                std::vector<int> counter (controlObject.initState.size()-1,0);
                counter[counter.size()-1] = -1;
                for(unsigned int k = 0; k<table[i][j].size();k++)
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


                    const auto& opt= table[i][j][k];
                    File<<t<<"\t"<<x0<<"\t";

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

}

void Control::printTable(double t)
{
    std::fstream File;
    unsigned int i = table.size()-1;
    unsigned int time = round(t*1000);
    File.open( "C:\\chwilowy\\mag\\"+std::to_string(time)+".txt", std::ios::out );
    if( File.good() == false)
    {
        std::cout<<"blad"<<std::endl;
        //std::cerr << "Error: " << strerror(errno);
        exit(250);
    }

    if(controlObject.stateValues.size() == 1)
    {
        for(unsigned int j = 0; j<controlObject.stateValues[0].size(); j++)
        {
            //std::cout<<j<<std::endl;
            const auto& opt= table[i][0][j];
            File<<controlObject.stateValues[0][j]<<";"<<opt.getU()<<";"<<opt.getCost()<<std::endl;
        }
    }
    else
    {
        for(unsigned int j = 0; j<controlObject.stateValues[0].size();j++)
        {
            const auto& x0 = controlObject.stateValues[0][j];

            std::vector<int> counter (controlObject.initState.size()-1,0);
            counter[counter.size()-1] = -1;
            for(unsigned int k = 0; k<table[i][j].size();k++)
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


                const auto& opt= table[i][j][k];
                File<<x0<<";";

                //for(int l = counter.size()-1; l>=0;l--)
                for(int l = 0; l<counter.size();l++)
                {
                    File<<controlObject.stateValues[l+1][counter[l]]<<";";
                }

                File<<opt.getU()<<";"<<opt.getCost()<<std::endl;
                //File<<opt.info<<std::endl;
            }
        }
    }

    table.erase(table.end()-1);

    File.close();

}

ControlPoint Control::findNearestPointFile(const std::vector<double>& xFind,const double t)
{
    std::fstream File;
    unsigned int time = t*1000;
    File.open( "C:\\chwilowy\\mag\\"+std::to_string(time)+".txt", std::ios::in );
    if( File.good() == false)
    {
        std::cout<<"blad "<<std::to_string(time)<<std::endl;
        //std::cerr << "Error: " << strerror(errno);
        exit(250);
    }

    std::vector<std::vector<double>> tab;
    std::string line;
    while (std::getline(File, line))
    {
        std::vector<double> vec;
        std::string::size_type sz;
        //std::cout<<line<<std::endl;
        for(int i = 0; i < xFind.size()+1; i++)
        {
            vec.push_back(std::stod(line,&sz));
            line = line.substr(sz+1);
            //std::this_thread::sleep_for(1s);
            //std::cout<<line<<std::endl;
        }
        vec.push_back(std::stod(line));
        //VecOpp::print(vec);
        //std::this_thread::sleep_for(5s);
        tab.push_back(vec);
    }

    File.close();

    std::vector<double> coordinates(xFind.size());

    for(unsigned int i = 0; i < coordinates.size(); i++)
    {
        coordinates[i] = findCoordinate(controlObject.stateValues[i],xFind[i]);
    }

    int offset = 0;
    int j = 1;
    for(int i = controlObject.stateValues.size()-1; i>=0;i--)
    {
        offset += coordinates[i]*j;
        //std::cout<<controlObject.stateValues[i].size()<<std::endl;
        j *= controlObject.stateValues[i].size();
        //std::cout<<j<<std::endl;
        //std::cout<<"offset"<<offset<<std::endl;
    }


    return ControlPoint(tab[offset][xFind.size()],tab[offset][xFind.size()+1]);
}
