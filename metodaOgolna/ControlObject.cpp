#include "ControlObject.h"
#include <math.h>
#include "VecOpp.h"
#include <iostream>

#define NUM 0


ControlObject::ControlObject() : dt(0.005), t0(0), tK(6.0), timeRes(0.02) //0.02
{
#if NUM == 0
    //std::cout << "start contructing ControlObject" << std::endl;
    initState = {0,0,-3.14/9,0};
    finState = {0,0,0,0};
    H = {
    {100000,0,0,0},
    {0,1000,0,0},
    {0,0,1000000,0},
    {0,0,0,100000}};

    Q = {
    {50,0,0,0},
    {0,1,0,0},
    {0,0,100,0},
    {0,0,0,10}};

    R = 0;

    stateValues = std::vector<std::vector<double>> (initState.size());
    // deff stateValues
    /*for(double val = -2; val<=2.09; val+=0.1)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        stateValues[0].push_back(val);
    }

    //for(double val = -50; val<=50; val+=1.0)
    //for(double val = -10; val<=10.1; val+=0.5)
    //{
    //    stateValues[1].push_back(val);
    //}
    stateValues[1] = {-10,-8,-7,-6,-5,-4.5,-4,-3.75,-3.5,-3.25,-3,-2.75,-2.5,-2.25,-2,-1.75,-1.5,-1.25,-1,-0.875,-0.75,-0.625,-0.5,-0.375,-0.25,-0.125,-0.125/2,-0.125/4,0,0.125/4,0.125/2,0.125,0.25,0.375,0.5,0.625,0.75,0.875,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.5,5,6,7,8,10};

    //for(double val = -3.14; val<=3.15; val+=3.14/36)
    ////for(double val = -3.14/9; val<=3.14/9; val+=3.14/(36*2))
    //{
    //    stateValues[2].push_back(val);
    //}
    stateValues[2] = {-3.14,-2.79,-2.44,-2.09,-1.92,-1.74,-1.57,-1.4,-1.22,-1.05,-0.87,-0.79,-0.7,-0.61,-0.52,-0.44,-0.35,-0.26,-0.22,-0.17,-0.13,-0.087,-0.07,-0.052,-0.035,-0.017,-0.009,0,0.009,0.017,0.035,0.052,0.07,0.087,0.13,0.17,0.22,0.26,0.35,0.44,0.52,0.61,0.7,0.79,0.87,1.05,1.22,1.4,1.57,1.74,1.92,2.09,2.44,2.79,3.14};

    //for(double val = -10; val<=10.01; val+=10.0/36)
    ////for(double val = -20/10; val<=20/10; val+=20.0/50)
    //{
    //    stateValues[3].push_back(val);
    //}
    stateValues[3] = {-10,-8,-7,-6,-5,-4.5,-4,-3.75,-3.5,-3.25,-3,-2.75,-2.5,-2.25,-2,-1.75,-1.5,-1.25,-1,-0.875,-0.75,-0.625,-0.5,-0.375,-0.25,-0.125,-0.125/2,-0.125/4,0,0.125/4,0.125/2,0.125,0.25,0.375,0.5,0.625,0.75,0.875,1,1.25,1.5,1.75,2,2.25,2.5,2.75,3,3.25,3.5,3.75,4,4.5,5,6,7,8,10};
    // end deff
*/
    /*for(double val = -2; val<=2.0009; val+=0.005)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -5; val<=5.0009; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -3.14; val<0; val+=3.14/72)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 0; val<=3.1401; val+=3.14/72)
    {
        stateValues[2].push_back(val);
    }
    for(double val = -3; val<=3.0009; val+=0.02)
    {
        stateValues[3].push_back(val);
    }*/


    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(double val = -1; val<-0.1-0.00001; val+=0.02)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -0.1; val<-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<0.1-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0.1; val<=1.0009; val+=0.02)
    {
        stateValues[0].push_back(val);
    }



    for(double val = -2; val<-0.25-0.0001; val+=0.25)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -0.25; val<-0.05-0.00001; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -0.05; val<0; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0; val<0.05-0.0001; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0.05; val<0.25-0.0001; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0.25; val<=2.0009; val+=0.25)
    {
        stateValues[1].push_back(val);
    }


    for(double val = -3.14/9; val<-3.14/36-0.001; val+=3.14/72)
    {
        stateValues[2].push_back(val);
    }
    for(double val = -3.14/36; val<-0.001; val+=3.14/288)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 0; val<3.14/36-0.001; val+=3.14/288)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 3.14/36; val<=3.1401/9; val+=3.14/72)
    {
        stateValues[2].push_back(val);
    }




    for(double val = -2; val<-0.101; val+=0.05)
    {
        stateValues[3].push_back(val);
    }
    for(double val = -0.1; val<-0.00001; val+=0.01)
    {
        stateValues[3].push_back(val);
    }
    stateValues[3].push_back(-0.005);
    stateValues[3].push_back(0);
    stateValues[3].push_back(0.005);
    for(double val = 0.01; val<0.10001; val+=0.01)
    {
        stateValues[3].push_back(val);
    }
    for(double val = 0.1; val<=2.0009; val+=0.05)
    {
        stateValues[3].push_back(val);
    }


    //for(double val = -50; val<=50.1; val+=2.5)
    for(double val = -10; val<=10.1; val+=0.5)
    {
        controlValues.push_back(val);
    }
#elif NUM == 1

    initState = {-1};
    finState = {0};
    H = {
    {100000000}};

    Q = {
    {1}};

    R = 0;

    std::vector<double> x0;
    for(double val = -1; val<=1.00009; val+=0.01)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        x0.push_back(val);
    }
    stateValues.push_back(x0);
    //std::cout<<stateValues.size()<<std::endl;

    for(double val = -10; val<=10.1; val+=0.5)
    {
        controlValues.push_back(val);
    }

    #elif NUM == 2

    initState = {10,0};
    finState = {0,0};
    H = {
    {0,0},
    {0,0}};

    Q = {
    {4,0},
    {0,0}};

    R = 1;

    stateValues = std::vector<std::vector<double>> (initState.size());
    //std::cout<<stateValues.size()<<std::endl;

    for(double val = -12; val<=12.0009; val+=0.1)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -20; val<=20.0009; val+=0.1)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -10; val<=10.001; val+=0.1)
    {
        controlValues.push_back(val);
    }

#elif NUM == 3

    initState = {1,0};
    finState = {0,0};
    H = {
    {1000000,0},
    {0,10000}};

    Q = {
    {10,0},
    {0,1}};

    R = 0;

    stateValues = std::vector<std::vector<double>> (initState.size());
    //std::cout<<stateValues.size()<<std::endl;

    //dt 1
    /*for(double val = -5; val<=5.0009; val+=1)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -5; val<=5.0009; val+=1)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -10; val<=10.001; val+=1)
    {
        controlValues.push_back(val);
    }*/

    //dt 0.1
    //for(double val = -2; val<=2.0009; val+=0.01) //opt -5 5 0.01 0.005
    //{
    //    stateValues[0].push_back(val);
    //}
    for(double val = -1; val<-0.1-0.00001; val+=0.02)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -0.1; val<-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<0.1-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0.1; val<=1.0009; val+=0.02)
    {
        stateValues[0].push_back(val);
    }

    //for(double val = -5; val<=5.0009; val+=0.1) //opt -5 5 0.1 //0.05
    //{
    //    stateValues[1].push_back(val);
    //}
    for(double val = -2; val<-0.25-0.0001; val+=0.25)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -0.25; val<-0.05-0.00001; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -0.05; val<0; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0; val<0.05-0.0001; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0.05; val<0.25-0.0001; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0.25; val<=2.0009; val+=0.25)
    {
        stateValues[1].push_back(val);
    }

    //std::cout<<stateValues[1].size()<<std::endl;


    for(double val = -10; val<=10.001; val+=0.5) //opt -10 10 1 // 0.5 konc
    {
        controlValues.push_back(val);
    }

#elif NUM == 4

    initState = {-3.14/36,0};
    finState = {0,0};
    H = {
    {1000000,0},
    {0,100000}};

    Q = {
    {100,0},
    {0,10}};

    R = 0;

    stateValues = std::vector<std::vector<double>> (initState.size());
    //std::cout<<stateValues.size()<<std::endl;

    //for(double val = -3.14; val<0; val+=3.14/72)
    //{
    //    stateValues[0].push_back(val);
    //}
    //for(double val = 0; val<=3.1401; val+=3.14/72)
    //{
    //    stateValues[0].push_back(val);
    //}

    for(double val = -3.14; val<-3.14/36-0.001; val+=3.14/72)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -3.14/36; val<-0.001; val+=3.14/288)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<3.14/36-0.001; val+=3.14/288)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 3.14/36; val<=3.1401; val+=3.14/72)
    {
        stateValues[0].push_back(val);
    }

    /*for(double val = -3.14; val<-3.14/2-0.001; val+=3.14/72)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -3.14/2; val<-3.14/36-0.001; val+=3.14/72)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -3.14/36; val<0.001; val+=3.14/288)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<3.14/36-0.001; val+=3.14/288)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 3.14/36; val<3.14/2-0.001; val+=3.14/72)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 3.14/2; val<=3.1401; val+=3.14/72)
    {
        stateValues[0].push_back(val);
    }*/


    //std::cout<<stateValues[0].size()<<std::endl;

    //for(double val = -2; val<=2.0009; val+=0.02)
    //{
    //    stateValues[1].push_back(val);
    //}
    for(double val = -2; val<-0.101; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -0.1; val<-0.00001; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0; val<0.10001; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0.1; val<=2.0009; val+=0.05)
    {
        stateValues[1].push_back(val);
    }

    /*for(double val = -2; val<-1.2-0.0001; val+=0.1)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -1.2; val<-0.1-0.0001; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -0.1; val<-0.00001; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0; val<0.1-0.0001; val+=0.01)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0.1; val<1.2-0.0001; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 1.2; val<=2.0009; val+=0.1)
    {
        stateValues[1].push_back(val);
    }*/

    //std::cout<<stateValues[1].size()<<std::endl;

    for(double val = -10; val<=10.001; val+=0.5)
    {
        controlValues.push_back(val);
    }


    #elif NUM == 5

    initState = {3,0,5,0};
    finState = {0,0,0,0};
    H = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,100,0},
    {0,0,0,100}};

    Q = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}};

    R = 0;

    stateValues = std::vector<std::vector<double>> (initState.size());
    //std::cout<<stateValues.size()<<std::endl;

    stateValues[0] = {-3,-2,-1,0,1,2,3};
    stateValues[1] = {-4,-3,-2,-1,0,1,2,3,4};
    stateValues[2] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
    stateValues[3] = {-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6};

    for(double val = -1; val<=1; val+=1)
    {
        controlValues.push_back(val);
    }
#endif // NUM

    //std::cout << "contructed ControlObject" << std::endl;

}

std::vector<double> ControlObject::diff (const std::vector<double>& x, const double t, const double u) const
{
    std::vector<double> dx(x.size());

#if NUM == 0

    dx[0] = x[1];
    dx[1] = u;
    dx[2] = x[3];
    dx[3] = -1.5 * u * cos(x[2]) + sin(x[2]);

#elif NUM == 1

    dx[0] = u;

#elif NUM == 2

    dx[0] = x[1];
    dx[1] = u;

#elif NUM == 3

    dx[0] = x[1];
    dx[1] = u;

#elif NUM == 4

    dx[0] = x[1];
    dx[1] = -1.5 * u * cos(x[0]) + sin(x[0]);

#elif NUM == 5

    dx[0] = x[1];
    dx[1] = u;
    dx[2] = x[3];
    dx[3] = u;

#endif // NUM

    return dx;
}

std::vector<double> ControlObject::xNext (const std::vector<double>& x, const double t, const double u, const double dt) const
{
    return VecOpp::add(x, VecOpp::mult(diff(x,t,u),dt));
}




double ControlObject::finCost (const std::vector<double>& x, const std::vector<double>& r) const
{
    std::vector<double> e = VecOpp::subt(x,r);
    return VecOpp::innerProd(e,VecOpp::mult(H,e));
}
double ControlObject::nextCost (const double dt) const
{
    return dt;
}

double ControlObject::nextCost (const double dt, const std::vector<double>& x, const std::vector<double>& r) const
{
    std::vector<double> e = VecOpp::subt(x,r);
    return VecOpp::innerProd(e,VecOpp::mult(Q,e))*dt;
}

double ControlObject::nextCost (const double dt, const std::vector<double>& x, const std::vector<double>& r, const double u)const
{
    std::vector<double> e = VecOpp::subt(x,r);
    return (VecOpp::innerProd(e,VecOpp::mult(Q,e))+u*R*u)*dt;
}

double ControlObject::nextCost (const double dt, const double t, const std::vector<double>& x, const std::vector<double>& r, const double u)const
{
    std::vector<double> e = VecOpp::subt(x,r);
    return (VecOpp::innerProd(e,VecOpp::mult(Q,e))*t+u*R*u)*dt;
}

