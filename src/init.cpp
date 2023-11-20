#include "init.h"

brain Brain;
controller* con = new controller(controllerType::primary);

Tank* chassis;
Mechanism* fourbar;

motor leftFront = motor(PORT17, ratio18_1, false);
motor leftBack = motor(PORT18, ratio18_1, false);

motor rightFront = motor(PORT19, ratio18_1, true);
motor rightBack = motor(PORT20, ratio18_1, true);

motor_group leftGroup = motor_group(leftFront, leftBack);
motor_group rightGroup = motor_group(rightFront, rightBack);

motor mech = motor(PORT11, ratio18_1, false);
motor_group mechGroup = motor_group(mech);

void init(void) {
    Brain.Screen.clearScreen();
    chassis = new Tank(12.5, 3.25/2.0, &leftGroup, &rightGroup, 1);
    chassis->setOffset(.25, 0.85);

    PID straight = PID(0.07, 0.008, 0);
    straight.bias = 2;
    straight.setErrorRange(2);
    PID turn = PID(0.06, 0.008, 0);
    turn.setErrorRange(2);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);

    chassis->setBrakeType(brakeType::brake);
    chassis->setMaxAcceleration(.5);

    // Fourbar setup
    fourbar = new Mechanism(&mechGroup, 0.25);
    PID lift = PID(0.3, 0.05, 0);
    fourbar->setPID(lift);
    fourbar->setBrakeType(brakeType::hold);
    fourbar->setMaxAcceleration(0);
    fourbar->setBounds(0, 90);
}

// TANK SETUP

// HDRIVE SETUP
    // chassis = new HDrive(
    //     12.5, 3.25/2.0, 3.25/2.0, 
    //     &leftGroup, &rightGroup, &centerGroup, 1);

    // PID straight = PID(.16, .05, .04);
    // PID turn = PID(.3, .065, .04);
    // PID strafe = PID(.3, .05, 0);

    // chassis->setStraightPID(straight);
    // chassis->setTurnPID(turn);
    // chassis->setStrafePID(strafe);

    // chassis->setMaxAcceleration(.25);

// ENCODER SETUP
// triport ThreeWirePort = triport(PORT22);
// encoder lenc = encoder(ThreeWirePort.B);
// encoder renc = encoder(ThreeWirePort.A);
// chassis->setEncoders(&lenc, &renc);