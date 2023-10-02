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


// triport ThreeWirePort = triport(PORT22);
// encoder lenc = encoder(ThreeWirePort.B);
// encoder renc = encoder(ThreeWirePort.A);


void init(void) {
    Brain.Screen.clearScreen();

    //8.5
    chassis = new Chassis(9.175, 11, 3.25/2.0, &leftGroup, &rightGroup);
    //chassis->setEncoders(&lenc, &renc);
    PID straight = PID(.15, .03, .04); // .04
    PID turn = PID(.3, .06, .05);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);

    chassis->setBrakeType(brakeType::brake);
}

void delay(int msec){
    wait(msec, timeUnits::msec);
}