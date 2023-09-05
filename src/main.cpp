#include "main.h"

competition Comp;

int main() {
    Comp.autonomous(auton);
    Comp.drivercontrol(usercontrol);
    init();
    while(1){usercontrol();}
}