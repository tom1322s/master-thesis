#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H
//#include <string>

class ControlPoint
{
    public:
        ControlPoint(double u, double cost);

        double getCost()const { return cost; }
        double getU()const { return u; }
        void setValues(double u, double cost) {this->u = u; this->cost = cost; }

        //std::string info;
    protected:

    private:
        double cost;
        double u;

};

#endif // CONTROLPOINT_H
