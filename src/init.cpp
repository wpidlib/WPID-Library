#include "init.h"

brain Brain;
controller* con = new controller(controllerType::primary);

Tank* chassis;

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
    chassis = new Tank(9.175, 3.25/2.0, &leftGroup, &rightGroup);
    chassis->setOffset(.25, -.75);
    //chassis->setEncoders(&lenc, &renc);

    PID straight = PID(.15, .035, .005); // .04
    straight.setErrorRange(1);

    PID turn = PID(.3, .06, .005);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);

    chassis->setBrakeType(brakeType::brake);
}

void delay(int msec){
    wait(msec, timeUnits::msec);
}