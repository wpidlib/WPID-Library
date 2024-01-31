#include "main.h"

competition Comp;

int main() {
    init();
    Comp.autonomous(auton);
    Comp.drivercontrol(usercontrol);

    while (1) {
        task::sleep(20);
    }
}