#ifndef CONTROLPOINT_H_INCLUDED
#define CONTROLPOINT_H_INCLUDED


/*struct ControlPoint
{
    public:
        ControlPoint():u(0),cost(1e30f){};
        ControlPoint(float u, float cost):u(u),cost(cost){};

        float getCost()const { return cost; };
        float getU()const { return u; };
        void setValues(float u, float cost) {this->u = u; this->cost = cost;};

    protected:

    private:
        float u;
        float cost;
};*/

struct ControlPoint
{
    public:
        //ControlPoint():u(0),cost(1e30f){};
        //ControlPoint(float u, float cost):u(u),cost(cost){};

        //float getCost()const { return cost; };
        //float getU()const { return u; };
        //void setValues(float u, float cost) {this->u = u; this->cost = cost;};

        float u;
        unsigned short cost;
};


#endif // CONTROLPOINT_H_INCLUDED
