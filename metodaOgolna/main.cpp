#include <iostream>
#include "test.h"
#include "ControlObject.h"
#include "Control.h"

using namespace std;

int main()
{
    //tests();

    ControlObject co;
    //cout<<"hi"<<endl;
    Control control (co);
    //cout<<"hi"<<endl;
    control.createTables();
    //control.printTables();
    control.simulate();
    control.showGraf();
    return 0;
}
