#include "AvaliableTable.h"
#include <iostream>

AvaliableTable::AvaliableTable(std::vector<std::vector<double>> states): states(states)
{
    numOfAllPoint = 1;
    for(const auto& v:states)
    {
        numOfAllPoint *= v.size();
    }

    unsigned long long sizeTable = numOfAllPoint / 32;

    if(numOfAllPoint % 32) sizeTable++;

    table = std::move(std::vector<unsigned int> (sizeTable,0));

    offsets = std::move(std::vector<unsigned int> (states.size(),1));
    for(size_t i = 0; i < states.size(); i++)
    {
        for(size_t j = i+1; j < states.size(); j++)
        {
            offsets[i]*=states[j].size();
        }
    }

    std::cout<<"Created AvaliableTable"<<std::endl;
    std::cout<<"NUM of Point : "<<numOfAllPoint<<std::endl;
}

bool AvaliableTable::getPoint(unsigned long long pos) const
{
    size_t bit = pos % 32;
    pos /=32;

    return table[pos] & 1<<bit;
}

void AvaliableTable::setPoint(unsigned long long pos)
{
    size_t bit = pos % 32;
    pos /=32;

    table[pos] |= 1<<bit;
}

size_t AvaliableTable::findCoordinate(const std::vector<double>& vec,const double num) const
{
    size_t i;
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

unsigned long long AvaliableTable::findCoordinates(const std::vector<double>& x) const
{
    unsigned long long pos=0;
    for(size_t i = 0; i < x.size(); i++)
    {
        pos += findCoordinate(states[i],x[i]) * offsets[i];
    }
    return pos;
}

bool AvaliableTable::getPoint(const std::vector<double>& x) const
{
    unsigned long long pos = findCoordinates(x);

    size_t bit = pos % 32;
    pos /=32;

    return table[pos] & 1<<bit;
}

void AvaliableTable::setPoint(const std::vector<double>& x)
{
    unsigned long long pos = findCoordinates(x);

    size_t bit = pos % 32;
    pos /=32;

    table[pos] |= 1<<bit;
}

std::vector<double> AvaliableTable::findState(unsigned long long pos) const
{
    std::vector<double> x;

    for(size_t i = 0; i < offsets.size(); i++)
    {
        x.push_back(states[i][pos/offsets[i]]);
        pos %= offsets[i];
    }
    return x;
}
