#ifndef CONTROL_H
#define CONTROL_H
#include <vector>
#include <string>
#include "ControlObject.h"
#include "ControlPoint.h"
#include "VecOpp.h"
#include "AvaliableTable.h"
#include <map>
#include <set>

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
        void setFinZeroCost(AvaliableTable& table, std::set<unsigned long long>& points);
        bool calculateOptimalControlValue(unsigned long long pos,ControlPoint& cp,const AvaliableTable& table, const unsigned int counter);
        std::map<unsigned long long,ControlPoint> iteratePoints0 (unsigned long long startPos, unsigned long long endPos, const AvaliableTable& table, const unsigned int counter);
        void updateTable(const std::map<unsigned long long,ControlPoint>& map, AvaliableTable& table, unsigned long long& numOfCountedPoints);

        std::set<unsigned long long> findSuspiciousPoints(const AvaliableTable& table,const std::set<unsigned long long>& points);
        std::set<unsigned long long> findSuspiciousPointsMultiThread(const AvaliableTable& table, const std::set<unsigned long long>& points,const unsigned int numOfThread,const unsigned int offset);

        std::map<unsigned long long,ControlPoint> iteratePoints (const std::set<unsigned long long>& points, const AvaliableTable& table, const unsigned int counter);
        std::map<unsigned long long,ControlPoint> iteratePointsMultiThread (const std::set<unsigned long long>& points, const unsigned int numOfThread,const unsigned int offset, const AvaliableTable& table, const unsigned int counter);

        std::set<unsigned long long> mapToSet (const std::map<unsigned long long,ControlPoint>& map);


        const ControlObject controlObject;
        std::string name;
};

#endif // CONTROL_H
