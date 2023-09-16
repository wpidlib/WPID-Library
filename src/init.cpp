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

    chassis = new Chassis((12.5 + 12.75) / 2.0, 3.25/2, &leftGroup, &rightGroup);
    // Original Constants : ki = 0.01, kp = 0.07, kd = 0.05
    // Second Iteration   : 0.15, 0.6, 0.015
    PID straight = PID(.15, .03, .04);
    straight.delay_time = 25;
    straight.bias = 0;  
    straight.setErrorRange(1);

    // old constants : 2, 0.02, 0
    PID turn = PID(.3, .05, 0);
    turn.setErrorRange(1);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);

    chassis->setBrakeType(brakeType::brake);
}

void delay(int msec){
    wait(msec, timeUnits::msec);
}