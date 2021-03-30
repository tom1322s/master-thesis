#ifndef CONTROLOBJECT_H
#define CONTROLOBJECT_H

#include <vector>


class ControlObject
{
    public:
        ControlObject();

        std::vector<double> diff (const std::vector<double>& x, const double t, const double u)const;
        std::vector<double> xNext (const std::vector<double>& x, const double t, const double u, const double dt)const;

        double finCost (const std::vector<double>& x, const std::vector<double>& r)const;
        double nextCost (const double dt)const;
        double nextCost (const double dt, const std::vector<double>& x, const std::vector<double>& r)const;
        double nextCost (const double dt, const std::vector<double>& x, const std::vector<double>& r, const double u)const;
        double nextCost (const double dt, const double t, const std::vector<double>& x, const std::vector<double>& r, const double u)const;


        std::vector<double> initState,finState;
        const double dt,t0,tK;

        std::vector<std::vector<double>> stateValues;
        std::vector<double> controlValues;
        const double timeRes;

        std::vector<std::vector<double>> H;
        std::vector<std::vector<double>> Q;
        double R;
    protected:

    private:

};

#endif // CONTROLOBJECT_H
