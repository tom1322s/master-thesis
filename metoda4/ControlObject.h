#ifndef CONTROLOBJECT_H
#define CONTROLOBJECT_H


#include <vector>


class ControlObject
{
    public:
        ControlObject();

        std::vector<double> diff (const std::vector<double>& x, const double u)const;
        std::vector<double> xNext (const std::vector<double>& x, const double u, const double dt)const;


        std::vector<double> initState,finState;
        const double dt,tK;

        std::vector<std::vector<double>> stateValues;
        std::vector<double> controlValues;
        const double timeRes;

        //unsigned long long numOfAllPoint;


    protected:

    private:

};

#endif // CONTROLOBJECT_H
