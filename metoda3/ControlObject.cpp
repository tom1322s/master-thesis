#include "ControlObject.h"
#include <math.h>
#include "VecOpp.h"
#include <iostream>

#define NUM 8
/*
#define EXP_1
#ifdef EXP_1

#define CODE_DEFINITION for(double val = -1.5; val<-0.5-0.0001; val+=0.1)\
{\
    stateValues[1].push_back(val);\
}

#define VELOCITY_SIZE 10
#define VELOCITY_SIZE2 20
#endif

struct temp_t
{
    int velocity[VELOCITY_SIZE];

    int velocity2[VELOCIT2Y_SIZE];
    float u[VELOCITY_SIZE * VELOCITY_SIZE2];
    float c[VELOCITY_SIZE * VELOCITY_SIZE2];

};
*/

ControlObject::ControlObject() : dt(0.016), tK(2) , timeRes(0.016) //0.02
{
#if NUM == 0
    //std::cout << "start contructing ControlObject" << std::endl;
    initState = {0,0,-3.14/288,0};
    finState = {0,0,0,0};


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
    // !!!!!!
    /*for(double val = -0.4; val<-0.1-0.00001; val+=0.01)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -0.1; val<-0.00001; val+=0.0025)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<0.1-0.00001; val+=0.0025)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0.1; val<=0.4009; val+=0.01)
    {
        stateValues[0].push_back(val);
    }



    for(double val = -1.5; val<-0.5-0.0001; val+=0.1)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -0.5; val<-0.05-0.00001; val+=0.05)
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
    for(double val = 0.05; val<0.5-0.0001; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0.5; val<=1.50009; val+=0.1)
    {
        stateValues[1].push_back(val);
    }


    for(double val = -3.14/9; val<-3.14/36-0.001; val+=3.14/144)
    {
        stateValues[2].push_back(val);
    }
    for(double val = -3.14/36; val<-0.001; val+=3.14/576)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 0; val<3.14/36-0.001; val+=3.14/576)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 3.14/36; val<=3.140001/9; val+=3.14/144)
    {
        stateValues[2].push_back(val);
    }




    for(double val = -2; val<-0.501; val+=0.05)
    {
        stateValues[3].push_back(val);
    }
    for(double val = -0.5; val<-0.00001; val+=0.02)
    {
        stateValues[3].push_back(val);
    }
    stateValues[3].push_back(-0.01);
    stateValues[3].push_back(0);
    stateValues[3].push_back(0.01);
    for(double val = 0.02; val<0.50001; val+=0.02)
    {
        stateValues[3].push_back(val);
    }
    for(double val = 0.5; val<=2.0009; val+=0.05)
    {
        stateValues[3].push_back(val);
    }


    //for(double val = -50; val<=50.1; val+=2.5)
    for(double val = -10; val<=10.1; val+=0.1)
    {
        controlValues.push_back(val);
    }*/


    for(double val = -0.2; val<-0.1-0.00001; val+=0.005)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -0.1; val<0-0.02-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -0.02; val<-0.00001; val+=0.001)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<0.02-0.00001; val+=0.001)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0.02; val<0.1-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0.1; val<=0.2009; val+=0.005)
    {
        stateValues[0].push_back(val);
    }




    //for(double val = -2; val<-0.5-0.00001; val+=0.05)
    //{
    //    stateValues[1].push_back(val);
    //}
    for(double val = -2; val<-0.00001; val+=0.025)
    {
        stateValues[1].push_back(val);
    }
    stateValues[1].push_back(-0.0125);
    stateValues[1].push_back(0);
    stateValues[1].push_back(0.0125);
    //for(double val = 0.02; val<0.5-0.00001; val+=0.025)
    //{
    //    stateValues[1].push_back(val);
    //}
    for(double val = 0.02; val<=2.0001; val+=0.025)
    {
        stateValues[1].push_back(val);
    }



    for(double val = -3.14/36; val<-3.14/36-0.001; val+=3.14/144)
    {
        stateValues[2].push_back(val);
    }
    for(double val = -3.14/36; val<-0.001; val+=3.14/4200)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 0; val<3.14/288-0.001; val+=3.14/4200)
    {
        stateValues[2].push_back(val);
    }
    //for(double val = 3.14/36; val<=3.140001/36; val+=3.14/144)
    //{
    //    stateValues[2].push_back(val);
    //}





    for(double val = -2; val<-0.5-0.00001; val+=0.05)
    {
        stateValues[3].push_back(val);
    }
    for(double val = -0.5; val<-0.00001; val+=0.025)
    {
        stateValues[3].push_back(val);
    }
    stateValues[3].push_back(-0.0125);
    stateValues[3].push_back(0);
    stateValues[3].push_back(0.0125);
    for(double val = 0.02; val<0.5-0.00001; val+=0.025)
    {
        stateValues[3].push_back(val);
    }
    for(double val = 0.5; val<=2.0001; val+=0.05)
    {
        stateValues[3].push_back(val);
    }



    //for(double val = -50; val<=50.1; val+=2.5)
    for(double val = -100; val<-5-0.001; val+=5)
    {
        controlValues.push_back(val);
    }
    for(double val = -5; val<-0.001; val+=2.5)
    {
        controlValues.push_back(val);
    }
    controlValues.push_back(-1.25);
    controlValues.push_back(0);
    controlValues.push_back(1.25);
    for(double val = 0.5; val<5-0.001; val+=2.5)
    {
        controlValues.push_back(val);
    }
    for(double val = 5; val<=100.1; val+=5)
    {
        controlValues.push_back(val);
    }
#elif NUM == 1

    initState = {-1};
    finState = {0};


    std::vector<double> x0;
    for(double val = -1; val<=1.00009; val+=0.01)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        x0.push_back(val);
    }
    stateValues.push_back(x0);
    //std::cout<<stateValues.size()<<std::endl;

    for(double val = -10; val<=10.1; val+=0.1)
    {
        controlValues.push_back(val);
    }

    #elif NUM == 2

    initState = {10,0};
    finState = {0,0};


    stateValues = std::vector<std::vector<double>> (initState.size());
    //std::cout<<stateValues.size()<<std::endl;

    for(double val = -10; val<=10.0009; val+=1)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -10; val<=10.0009; val+=1)
    //for(double val = -0.5; val<=0.5; val+=0.05)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -1; val<=1.001; val+=1.0)
    {
        controlValues.push_back(val);
    }

#elif NUM == 3

    initState = {1,0};
    finState = {0,0};


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


    for(double val = -10; val<=10.001; val+=0.1) //opt -10 10 1 // 0.5 konc
    {
        controlValues.push_back(val);
    }

#elif NUM == 4

    initState = {-3.14/36,0};
    finState = {0,0};


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

    initState = {3,0,3,0};
    finState = {0,0,0,0};

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

#elif NUM == 6

    //std::cout << "start contructing ControlObject" << std::endl;
    //initState = {0,-3.14/288,0};
    initState = {0,-3.14,0};
    finState = {0,0,0};


    stateValues = std::vector<std::vector<double>> (initState.size());



    for(double val = -1; val<-0.1-0.00001; val+=0.01)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -0.1; val<0-0.02-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -0.02; val<-0.00001; val+=0.001)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<0.02-0.00001; val+=0.001)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0.02; val<0.1-0.00001; val+=0.002)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0.1; val<=1.009; val+=0.01)
    {
        stateValues[0].push_back(val);
    }



    for(double val = -3.14; val<-3.14/36-0.001; val+=3.14/144)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -3.14/36; val<-0.001; val+=3.14/4200)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0; val<3.14/36-0.001; val+=3.14/4200)
    {
        stateValues[1].push_back(val);
    }
    //for(double val = 3.14/36; val<=3.140001/36; val+=3.14/144)
    //{
    //    stateValues[1].push_back(val);
    //}




    for(double val = -20; val<-5-0.00001; val+=5*((3.14/4200)/timeRes))
    {
        stateValues[2].push_back(val);
    }
    for(double val = -5; val<-0.00001; val+=(3.14/4200)/timeRes)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 0; val<5-0.00001; val+=(3.14/4200)/timeRes)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 5; val<=20.0001; val+=5*((3.14/4200)/timeRes))
    {
        stateValues[2].push_back(val);
    }



    //for(double val = -50; val<=50.1; val+=2.5)
    for(double val = -5*(((3.14/4200)/timeRes)/timeRes); val<-0.001; val+=((3.14/4200)/timeRes)/timeRes)
    {
        controlValues.push_back(val);
    }
    for(double val = 0; val<=5*(((3.14/4200)/timeRes)/timeRes)+0.001; val+=((3.14/4200)/timeRes)/timeRes)
    {
        controlValues.push_back(val);
    }

#elif NUM == 7

    //std::cout << "start contructing ControlObject" << std::endl;
    //initState = {0,-3.14/288,0};
    initState = {0,0,-3.14,0};
    finState = {0,0,0,0};

    double dx = 0.005;
    double dv = dx/timeRes;
    double da = 3.14/2100;
    double dom = da/timeRes;
    double du = dv/timeRes;


    stateValues = std::vector<std::vector<double>> (initState.size());




    for(double val = -0.5; val<-50*dx-0.00001; val+=5*dx)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -50*dx; val<-0.00001; val+=dx)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<50*dx-0.00001; val+=dx)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 50*dx; val<=0.509; val+=5*dx)
    {
        stateValues[0].push_back(val);
    }


    for(double val = -20; val<-20*dv-0.00001; val+=4*dv)
    {
        stateValues[1].push_back(val);
    }
    for(double val = -20*dv; val<-0.00001; val+=dv)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 0; val<20*dv-0.00001; val+=dv)
    {
        stateValues[1].push_back(val);
    }
    for(double val = 20*dv; val<=20.0001; val+=4*dv)
    {
        stateValues[1].push_back(val);
    }



    for(double val = -3.14; val<-3.14/36-0.001; val+=5*da)
    {
        stateValues[2].push_back(val);
    }
    for(double val = -3.14/36; val<-0.001; val+=da)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 0; val<3.14/36-0.001; val+=da)
    {
        stateValues[2].push_back(val);
    }
    //for(double val = 3.14/36; val<=3.140001/36; val+=3.14/144)
    //{
    //    stateValues[1].push_back(val);
    //}




    for(double val = -20; val<-5-0.00001; val+=5*dom)
    {
        stateValues[3].push_back(val);
    }
    for(double val = -5; val<-0.00001; val+=dom)
    {
        stateValues[3].push_back(val);
    }
    for(double val = 0; val<5-0.00001; val+=dom)
    {
        stateValues[3].push_back(val);
    }
    for(double val = 5; val<=20.0001; val+=5*dom)
    {
        stateValues[3].push_back(val);
    }



    //for(double val = -50; val<=50.1; val+=2.5)
    for(double val = -5*du; val<-0.001; val+=du)
    {
        controlValues.push_back(val);
    }
    for(double val = 0; val<=5*du+0.001; val+=du)
    {
        controlValues.push_back(val);
    }


#elif NUM == 8

    //std::cout << "start contructing ControlObject" << std::endl;
    //initState = {0,-3.14/288,0};
    initState = {0,0,-3.14,0};
    finState = {0,0,0,0};

    double dx = 0.0005;
    double dv = dx/timeRes;
    double da = 3.14/2100;
    double dom = da/timeRes;
    double du = dom/timeRes;


    stateValues = std::vector<std::vector<double>> (initState.size());




    for(double val = -0.25; val<-50*dx-0.00001; val+=5*dx)
    {
        stateValues[0].push_back(val);
    }
    for(double val = -50*dx; val<-0.00001; val+=dx)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 0; val<50*dx-0.00001; val+=dx)
    {
        stateValues[0].push_back(val);
    }
    for(double val = 50*dx; val<=1.0009; val+=5*dx)
    {
        stateValues[0].push_back(val);
    }


    //for(double val = -3.5; val<-10*dv-0.00001; val+=4*dv)
    //{
    //    stateValues[1].push_back(val);
    //}
    for(double val = -3.5; val<-0.00001; val+=dv)
    {
        stateValues[1].push_back(val);
    }
    //for(double val = 0; val<20*dv-0.00001; val+=dv)
    //{
    //    stateValues[1].push_back(val);
    //}
    for(double val = 0; val<=3.5001; val+=dv)
    {
        stateValues[1].push_back(val);
    }



    for(double val = -3.14; val<-3.14/36-0.001; val+=5*da)
    {
        stateValues[2].push_back(val);
    }
    for(double val = -3.14/36; val<-0.001; val+=da)
    {
        stateValues[2].push_back(val);
    }
    for(double val = 0; val<3.14/9-0.001; val+=da)
    {
        stateValues[2].push_back(val);
    }
    //for(double val = 3.14/36; val<=3.140001/36; val+=3.14/144)
    //{
    //    stateValues[1].push_back(val);
    //}




    //for(double val = -7; val<-3.5-0.00001; val+=10*dom)
    //{
    //    stateValues[3].push_back(val);
    //}
    //for(double val = -3.5; val<-0.00001; val+=dom)
    for(double val = -1; val<-0.00001; val+=dom)
    {
        stateValues[3].push_back(val);
    }
    for(double val = 0; val<3.5-0.00001; val+=dom)
    {
        stateValues[3].push_back(val);
    }
    for(double val = 3.5; val<=5.0001; val+=10*dom)
    {
        stateValues[3].push_back(val);
    }



    //for(double val = -50; val<=50.1; val+=2.5)
    for(double val = -2*du; val<-0.001; val+=du)
    {
        controlValues.push_back(val);
    }
    for(double val = 0; val<=2*du+0.001; val+=du)
    {
        controlValues.push_back(val);
    }
#endif // NUM


   /* numOfAllPoint = 1;
    for(const auto& v:stateValues)
    {
        numOfAllPoint *= v.size();
    }


    std::cout << numOfAllPoint << std::endl;
    //std::cout << "contructed ControlObject" << std::endl;*/

}

std::vector<double> ControlObject::diff (const std::vector<double>& x, const double u) const
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

#elif NUM == 6

    dx[0] = u*timeRes;
    dx[1] = x[2];
    dx[2] = -1.5 * u * cos(x[1]) + sin(x[1]);

#elif NUM == 7

    dx[0] = x[1];
    dx[1] = u-(5*312.5/20)*x[1];
    dx[2] = x[3];
    dx[3] = -1.5 * u * cos(x[2]) + sin(x[2]);

#elif NUM == 8

    dx[0] = x[1];
    dx[1] = u-(2.5/20)*x[1];
    dx[2] = x[3];
    dx[3] = -1.5 * dx[1] * cos(x[2]) + sin(x[2]);

#endif // NUM

    return dx;
}

std::vector<double> ControlObject::xNext (const std::vector<double>& x, const double u, const double dt) const
{
    return VecOpp::add(x, VecOpp::mult(diff(x,u),dt));
}

