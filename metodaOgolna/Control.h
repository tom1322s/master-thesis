#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>
#include "ControlObject.h"
#include "ControlPoint.h"

class Control
{
    public:
        Control(const ControlObject& controlObject);
        void createTables();
        void simulate();
        void showGraf();
        void printTables();


        //ControlPoint findNearestPoint(const std::vector<double>& xFind);
        int findCoordinate(const std::vector<double>& vec,const double num);


    protected:

    private:
        ControlPoint calculateOptimalControlValue(double t, const std::vector<double>& x);
        std::vector<ControlPoint> createMiniTables(double t,const std::vector<double> x, size_t index);
        ControlPoint findNearestPoint(const std::vector<double>& xFind,const size_t index=0);
        ControlPoint findNearestPointFile(const std::vector<double>& xFind,const double t);
        //int findCoordinate(const std::vector<double>& vec,const double num);
        void printTable(double t);



        const ControlObject controlObject;
        std::string name;
        std::vector<std::vector<std::vector<ControlPoint>>> table;

};

#endif // CONTROL_H
