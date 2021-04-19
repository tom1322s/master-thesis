#ifndef CONTROLPOINT_H_INCLUDED
#define CONTROLPOINT_H_INCLUDED
/*
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

};*/

class ControlPoint
{
    public:
        ControlPoint():u(0),cost(1e30f),avaliable(false){};
        ControlPoint(float u, float cost, bool avaliable):u(u),cost(cost),avaliable(avaliable){};

        float getCost()const { return cost; };
        float getU()const { return u; };
        bool getAvaliable()const { return avaliable; };
        void setValues(float u, float cost, bool avaliable) {this->u = u; this->cost = cost; this->avaliable=avaliable;};

    protected:

    private:
        float u;
        float cost;
        bool avaliable;

};


#endif // CONTROLPOINT_H_INCLUDED
