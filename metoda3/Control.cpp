#include "Control.h"
#include "BinaryFile.h"
#include <thread>
#include <future>


Control::Control(const ControlObject& controlObject) : controlObject(controlObject)
{
    name = "methodTable.data";
}


void Control::createTables()
{
    AvaliableTable table(controlObject.stateValues);

    prepareTable(table.getNumOfAllPoint());

    setFinZeroCost(table);

    bool finish = false;
    unsigned long long numOfCountedPoint = 1;
    unsigned long long prevNumOfCountedPoint = 1;
    unsigned int numOfThread = std::thread::hardware_concurrency();
    std::cout<<"Num of thread = "<<numOfThread<<std::endl;


    for(unsigned short counter = 1; !finish ; counter++)
    {
        unsigned long long threadPointPart = table.getNumOfAllPoint()/numOfThread;

        std::map<unsigned long long,ControlPoint> mapPoint;

        std::vector<std::future<std::map<unsigned long long,ControlPoint>>> threads;

        for(unsigned int i = 0; i < numOfThread; i++)
        {
            unsigned long long startPoint = i * threadPointPart;
            unsigned long long endPoint;
            if(i == numOfThread - 1) endPoint = table.getNumOfAllPoint();
            else endPoint = startPoint + threadPointPart;

            threads.push_back(std::async(std::launch::async, &Control::iteratePoints, this,startPoint,endPoint,table,counter));
        }

        for(auto& thread:threads)
        {
            auto res = thread.get();
            mapPoint.merge(std::move(res));
            if(res.size()>0)
            {
                std::cout<<"Map merge Error"<<std::endl;
                exit(150);
            }
        }
        std::cout<<"Nowe punkty = "<<mapPoint.size()<<std::endl;

        updateTable(mapPoint,table,numOfCountedPoint);


        std::cout<<"fin iteration " << counter << std::endl<<std::endl;
        std::cout<<numOfCountedPoint<<"/"<<table.getNumOfAllPoint()<<std::endl;
        std::cout<<(numOfCountedPoint*100.0)/table.getNumOfAllPoint()<<std::endl<<std::endl;
        //printTables(std::to_string(counter));

        if(prevNumOfCountedPoint==numOfCountedPoint)
        {
            finish = true;
        }
        else
        {
            prevNumOfCountedPoint = numOfCountedPoint;
            finish = false;
        }
    }
}

void Control::prepareTable(unsigned long long num)
{
    BinaryFile bf(name,bf.MODE_WRITE);
    bf.prepareFile(num);
}

void Control::setFinZeroCost(AvaliableTable& table)
{
    auto pos = table.findCoordinates(controlObject.finState);

    table.setPoint(pos);

    ControlPoint cp;
    cp.u=0;
    cp.cost=0;

    BinaryFile bf(name,bf.MODE_MODIFY);
    bf.setControlPoint(pos,cp);
}

bool Control::calculateOptimalControlValue(unsigned long long pos,ControlPoint& cp,const AvaliableTable& table, const unsigned int counter)
{
    bool success = false;
    for(const auto& u: controlObject.controlValues)
    {
        std::vector<double> x = table.findState(pos);
        std::vector<double> xNext = controlObject.xNext(x,u,controlObject.timeRes);
        unsigned long long nextPos = table.findCoordinates(xNext);

        //double distance;
        //ControlPoint next = findNearestPoint(xNext,distance);

        if(table.getPoint(nextPos))
        {
            auto cost = counter;

            cp.u = u;
            cp.cost = cost;
            success = true;

        }
    }

    return success;
}

std::map<unsigned long long,ControlPoint> Control::iteratePoints (unsigned long long startPos, unsigned long long endPos, const AvaliableTable& table, const unsigned int counter)
{
    std::map<unsigned long long,ControlPoint> result;
    size_t p = 1;
    unsigned long long nums = (endPos-startPos)/10;
    for(unsigned long long i = startPos; i < endPos; i++)
    {
        if(i>=startPos+nums*p)
        {
            std::cout<<p*10<<" ";
            p++;
        }
        if(!table.getPoint(i))
        {
            //std::cout<<"pos "<<i<<std::endl;
            //VecOpp::print(table.findState(i));
            ControlPoint opt;
            if(calculateOptimalControlValue(i,opt,table,counter))
            {
                //std::cout<<"for : "<<i<<std::endl;
                result.emplace(i,opt);
            }
        }
    }
    return result;
}

void Control::updateTable(const std::map<unsigned long long,ControlPoint>& map, AvaliableTable& table, unsigned long long& numOfCountedPoints)
{
    BinaryFile bf(name,bf.MODE_MODIFY);
    for (const auto &p : map)
    {
        bf.setControlPoint(p.first,p.second);
        table.setPoint(p.first);
        numOfCountedPoints++;
    }
}


void Control::simulate()
{
    AvaliableTable table(controlObject.stateValues);
    BinaryFile bf(name,bf.MODE_READ);
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

    //std::vector<double> xT(xId.size()),xT2(xId.size()),xT3(xId.size());

    for(unsigned int i = 0; i<=controlObject.tK/controlObject.dt;i++)
    {
        double t = i*controlObject.dt;

        if(t>=j*controlObject.timeRes)
        {
            auto opt= bf.getControlPoint(table.findCoordinates(xSim));
            uSim = opt.u;
            cSim = opt.cost;

            opt= bf.getControlPoint(table.findCoordinates(xId));
            uId = opt.u;
            cId = opt.cost;

            opt= bf.getControlPoint(table.findCoordinates(xIdDysk));
            uIdDysk = opt.u;
            cIdDysk = opt.cost;
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



        std::vector<double> dx = controlObject.diff(xSim,uSim);
        xSim = VecOpp::add(xSim,VecOpp::mult(dx,controlObject.dt));

        if(t>=j*controlObject.timeRes)
        {
            dx = controlObject.diff(xId,uId);
            xId = VecOpp::add(xId,VecOpp::mult(dx,controlObject.timeRes));
            dx = controlObject.diff(xIdDysk,uIdDysk);
            xIdDysk = VecOpp::add(xIdDysk,VecOpp::mult(dx,controlObject.timeRes));

            xIdDysk = table.findState(table.findCoordinates(xIdDysk));

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
