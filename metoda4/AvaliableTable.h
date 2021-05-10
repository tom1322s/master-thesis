#ifndef AVALIABLETABLE_H
#define AVALIABLETABLE_H

#include <vector>
#include <set>


class AvaliableTable
{
    public:
        AvaliableTable(std::vector<std::vector<double>> states);

        bool getPoint(unsigned long long pos) const;
        void setPoint(unsigned long long pos);
        bool getPoint(const std::vector<double>& x) const;
        void setPoint(const std::vector<double>& x);

        unsigned long long findCoordinates(const std::vector<double>& x) const;
        std::vector<double> findState(unsigned long long pos) const;

        std::set<unsigned long long> findNeighbors(unsigned long long pos) const;


        unsigned long long getNumOfAllPoint()const{return numOfAllPoint;};

    protected:

    private:

        size_t findCoordinate(const std::vector<double>& vec,const double num)const;

        unsigned long long numOfAllPoint;
        std::vector<unsigned int> table;
        std::vector<std::vector<double>> states;
        std::vector<unsigned int> offsets;
};

#endif // AVALIABLETABLE_H
