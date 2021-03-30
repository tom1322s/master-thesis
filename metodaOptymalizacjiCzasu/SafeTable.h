#ifndef SAFETABLE_H
#define SAFETABLE_H

#include <mutex>
#include <vector>
#include <atomic>
#include "ControlPoint.h"


class SafeTable
{
    public:
        SafeTable(const std::vector<std::vector<double>>& stateValues)
        {
            if(stateValues.size() == 1)
            {
                std::vector<ControlPoint> value;
                for(size_t i = 0; i < stateValues[0].size();i++)
                {
                    value.push_back(ControlPoint());
                }
                table.push_back(value);
            }
            else
            {
                unsigned int num = 1;

                for(size_t i = 1; i < stateValues.size();i++)
                {
                    num*= stateValues[i].size();
                }

                std::vector<ControlPoint> value;
                for(size_t i = 0; i < stateValues[0].size();i++)
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
        }

        ControlPoint get(size_t i, size_t j)
        {
            std::lock_guard<std::mutex> lk(mut);
            return table[i][j];
        }

        void set(size_t i, size_t j,const ControlPoint& cp)
        {
            std::lock_guard<std::mutex> lk(mut);
            table[i][j] = cp;
        }

        size_t getSize(size_t i)
        {
            std::lock_guard<std::mutex> lk(mut);
            return table[i].size();
        }
    protected:

    private:
        std::vector<std::vector<ControlPoint>> table;
        mutable std::mutex mut;
};


/*class SafeTable
{
    public:
        SafeTable(const std::vector<std::vector<double>>& stateValues)
        {
            if(stateValues.size() == 1)
            {
                std::vector<std::atomic<ControlPoint>> value;
                for(size_t i = 0; i < stateValues[0].size();i++)
                {
                    std::atomic<ControlPoint> a (ControlPoint());
                    value.emplace_back(std::move(a));
                }
                //table.push_back(value);
            }
            else
            {
                unsigned int num = 1;

                for(size_t i = 1; i < stateValues.size();i++)
                {
                    num*= stateValues[i].size();
                }

                std::vector<std::atomic<ControlPoint>> value;
                for(size_t i = 0; i < stateValues[0].size();i++)
                {
                    std::vector<std::atomic<ControlPoint>> value;
                    value.reserve(num);
                    for(size_t j = 0; j < num;j++)
                    {
                        value.push_back(std::atomic<ControlPoint>(ControlPoint()));
                    }
                    table.push_back(value);
                }
            }
        }

        ControlPoint get(size_t i, size_t j)
        {
            //return table[i][j].load();
        }

        void set(size_t i, size_t j,const ControlPoint& cp)
        {
            //table[i][j].store(cp);
        }

        size_t getSize(size_t i)
        {
            return table[i].size();
        }
    protected:

    private:
        std::vector<std::vector<std::atomic<ControlPoint>>> table;
        //mutable std::mutex mut;
};*/

#endif // SAFETABLE_H
