#include "main.h"

using namespace vex;

brain Brain;
controller Controller;

Chassis* chassis;

void vexcodeInit(void) {
    int motorL[2] = {1, 9};
    int motorR[2] = {2, 10};
    chassis = new Chassis((12.5 + 12.75) / 2, 3.375, motorL, motorR);
}