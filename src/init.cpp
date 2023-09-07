#include "main.h"

using namespace vex;

brain Brain;
controller* con = new controller(controllerType::primary);

Chassis* chassis;

motor leftFront = motor(PORT1, ratio18_1, false);
motor leftBack = motor(PORT10, ratio18_1, false);
motor rightFront = motor(PORT2, ratio18_1, true);
motor rightBack = motor(PORT10, ratio18_1, true);

motor_group leftGroup = motor_group(leftFront, leftBack);
motor_group rightGroup = motor_group(rightFront, rightBack);

void init(void) {
    Brain.Screen.clearScreen();
    chassis = new Chassis((12.5 + 12.75) / 2, 3.375/2, &leftGroup, &rightGroup);
    chassis->setBrakeType(brakeType::hold);
}

void delay(int msec){
    wait(msec, timeUnits::msec);
}