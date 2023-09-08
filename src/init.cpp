#include "main.h"

using namespace vex;

brain Brain;
controller* con = new controller(controllerType::primary);

Chassis* chassis;

motor leftFront = motor(PORT9, ratio18_1, false);
motor leftBack = motor(PORT1, ratio18_1, false);
motor rightFront = motor(PORT10, ratio18_1, true);
motor rightBack = motor(PORT2, ratio18_1, true);

motor_group leftGroup = motor_group(leftFront, leftBack);
motor_group rightGroup = motor_group(rightFront, rightBack);

void init(void) {
    Brain.Screen.clearScreen();

    chassis = new Chassis((12.5 + 12.75) / 2, 3.375/2, &leftGroup, &rightGroup);

    PID straight = PID(0.2, 0, 0);
    straight.setErrorRange(5);

    PID turn = PID(2, 0, 0);
    straight.setErrorRange(5);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);

    chassis->setBrakeType(brakeType::hold);


}

void delay(int msec){
    wait(msec, timeUnits::msec);
}