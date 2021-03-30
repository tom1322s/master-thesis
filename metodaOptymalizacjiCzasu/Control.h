#ifndef CONTROL_H
#define CONTROL_H
#include <vector>
#include <string>
#include "ControlObject.h"
#include "ControlPoint.h"
#include "VecOpp.h"
#include "SafeTable.h"

#define THREAD 1

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
        bool miniTables(size_t tinx, const std::vector<double> x, size_t index, unsigned int offset);
        ControlPoint findNearestPoint(const std::vector<double>& xFind);
        ControlPoint findNearestPoint(const std::vector<double>& xFind,double& distance);
        int findCoordinate(const std::vector<double>& vec,const double num);
        void setFinZeroCost();



        const ControlObject controlObject;
        unsigned int numOfCountedPoint=0;
        std::string name;
        unsigned int globalCounter;
#if THREAD == 0
        std::vector<std::vector<ControlPoint>> table;
#else
        SafeTable safeTable;
#endif // THREAD

};

#endif // CONTROL_H
