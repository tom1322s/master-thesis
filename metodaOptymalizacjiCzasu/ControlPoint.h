#ifndef CONTROLPOINT_H_INCLUDED
#define CONTROLPOINT_H_INCLUDED

class ControlPoint
{
    public:
        ControlPoint():u(0),cost(1e300),avaliable(false){};
        ControlPoint(double u, double cost, bool avaliable):u(u),cost(cost),avaliable(avaliable){};

        double getCost()const { return cost; };
        double getU()const { return u; };
        bool getAvaliable()const { return avaliable; };
        void setValues(double u, double cost, bool avaliable) {this->u = u; this->cost = cost; this->avaliable=avaliable;};

    protected:

    private:
        double u;
        double cost;
        bool avaliable;

};


#endif // CONTROLPOINT_H_INCLUDED
