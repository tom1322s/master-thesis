#include "test.h"
#include "VecOpp.h"
#include <cassert>
#include "Control.h"


void tests()
{
    vecOppTest();
    findCoordinateTest();
}

void vecOppTest()
{
    std::vector<double> a = {1,1,2,1};
    std::vector<double> b = {1,1,1,2};
    std::vector<std::vector<double>> m{{10,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    VecOpp::print(VecOpp::add(a,b));
    assert((VecOpp::add(a,b)==(std::vector<double>) {2,2,3,3}));
    VecOpp::print(VecOpp::subt(a,b));
    assert((VecOpp::subt(a,b)==(std::vector<double>) {0,0,1,-1}));
    VecOpp::print(VecOpp::mult(a,2));
    assert((VecOpp::mult(a,2)==(std::vector<double>) {2,2,4,2}));
    VecOpp::print(VecOpp::mult(2,b));
    assert((VecOpp::mult(2,b)==(std::vector<double>) {2,2,2,4}));
    std::cout << VecOpp::innerProd(a,VecOpp::mult(m,a))<<std::endl;
    assert((VecOpp::innerProd(a,VecOpp::mult(m,a))==16));
}

void findCoordinateTest()
{
    ControlObject co;
    Control control (co);
    std::vector<double> v = {-10,-8,-6,-4,-2,0,2,4,6,8,10};
    assert(0 == control.findCoordinate(v,-12));
    std::cout << control.findCoordinate(v,-12)<<std::endl;
    assert(0 == control.findCoordinate(v,-10));
    std::cout << control.findCoordinate(v,-10)<<std::endl;
    assert(0 == control.findCoordinate(v,-9.5));
    std::cout << control.findCoordinate(v,-9.5)<<std::endl;
    assert(0 == control.findCoordinate(v,-9));
    std::cout << control.findCoordinate(v,-9)<<std::endl;
    assert(1 == control.findCoordinate(v,-8.5));
    std::cout << control.findCoordinate(v,-8.5)<<std::endl;
    assert(4 == control.findCoordinate(v,-1.5));
    std::cout << control.findCoordinate(v,-1.5)<<std::endl;
    assert(9 == control.findCoordinate(v,7.5));
    std::cout << control.findCoordinate(v,7.5)<<std::endl;
    assert(9 == control.findCoordinate(v,8));
    std::cout << control.findCoordinate(v,8)<<std::endl;
    assert(9 == control.findCoordinate(v,8.5));
    std::cout << control.findCoordinate(v,8.5)<<std::endl;
    assert(9 == control.findCoordinate(v,9));
    std::cout << control.findCoordinate(v,9)<<std::endl;
    assert(10 == control.findCoordinate(v,9.5));
    std::cout << control.findCoordinate(v,9.5)<<std::endl;
    assert(10 == control.findCoordinate(v,10));
    std::cout << control.findCoordinate(v,10)<<std::endl;
    assert(10 == control.findCoordinate(v,12));
    std::cout << control.findCoordinate(v,12)<<std::endl;
}
