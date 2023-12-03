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
    chassis = new Tank(12.5, 1.625, &leftGroup, &rightGroup, 1);
    chassis->setOffset(.25, 0.85);
    chassis->setBrakeType(brakeType::brake);
    chassis->setMaxAcceleration(.5);
    chassis->setMeasurementUnits(Conversion::measurement::in);


    PID straight = PID(0.3, 0.65, 0.04);
    straight.setBias(0);
    straight.setMaxIntegral(8);
    straight.setLowSpeedThreshold(3);
    straight.setDelayTime(25);
    straight.setErrorRange(2);

    PID turn = PID(0.06, 0.008, 0.001);
    turn.setErrorRange(2);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);

    // Fourbar setup
    fourbar = new Mechanism(&mechGroup, 0.25);
    fourbar->setBrakeType(brakeType::hold);
    fourbar->setMaxAcceleration(0);
    fourbar->setBounds(0, 90);

    PID lift = PID(0.3, 0.05, 0.001);
    fourbar->setPID(lift);

    LOG().setBaseLevel(DEBUG);
    LOG(INFO) << "Robot Initialized";
}