#ifndef CONTROL_H
#define CONTROL_H
#include <vector>
#include <string>
#include "ControlObject.h"
#include "ControlPoint.h"
#include "VecOpp.h"


class Control
{
    public:
        Control(const ControlObject& controlObject);
        void createTables();
        void simulate();
        void showGraf();
        void printTables(std::string name);


        //ControlPoint findNearestPoint(const std::vector<double>& xFind);
        //int findCoordinate(const std::vector<double>& vec,const double num);


    protected:

    private:
        bool calculateOptimalControlValue(const std::vector<double>& x,ControlPoint& cp);
        std::vector<ControlPoint> createMiniTables(const std::vector<double> x, size_t index);
        ControlPoint findNearestPoint(const std::vector<double>& xFind);
        ControlPoint findNearestPoint(const std::vector<double>& xFind,double& distance);
        int findCoordinate(const std::vector<double>& vec,const double num);
        void setFinZeroCost();



        const ControlObject controlObject;
        unsigned int numOfCountedPoint=0;
        std::string name;
        unsigned int globalCounter;

        std::vector<std::vector<ControlPoint>> table;


};

#endif // CONTROL_H
