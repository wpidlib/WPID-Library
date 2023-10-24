#include "main.h"

competition Comp;

int main() {
    init();
    Comp.autonomous(auton);
    Comp.drivercontrol(usercontrol);

    while (1) {
        wait(20, msec);
    }
}