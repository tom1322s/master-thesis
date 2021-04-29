#ifndef CONTROL_H
#define CONTROL_H
#include <vector>
#include <string>
#include "ControlObject.h"
#include "ControlPoint.h"
#include "VecOpp.h"
#include "AvaliableTable.h"
#include <map>

class Control
{
    public:
        Control(const ControlObject& controlObject);

        void createTables();
        void simulate();
        void showGraf();

    protected:

    private:
        void prepareTable(unsigned long long num);
        void setFinZeroCost(AvaliableTable& table);
        bool calculateOptimalControlValue(unsigned long long pos,ControlPoint& cp,const AvaliableTable& table, const unsigned int counter);
        std::map<unsigned long long,ControlPoint> iteratePoints (unsigned long long startPos, unsigned long long endPos, const AvaliableTable& table, const unsigned int counter);
        void updateTable(const std::map<unsigned long long,ControlPoint>& map, AvaliableTable& table, unsigned long long& numOfCountedPoints);


        const ControlObject controlObject;
        std::string name;
};

#endif // CONTROL_H
