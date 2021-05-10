#include <iostream>
#include "ControlObject.h"
#include "Control.h"

using namespace std;

int main()
{
    ControlObject co;
    Control control (co);

    control.createTables();
    control.simulate();
    control.showGraf();
    return 0;
}
