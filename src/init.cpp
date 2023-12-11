#include "init.h"

brain Brain;
controller* con = new controller(controllerType::primary);

HDrive* chassis;
Mechanism* fourbar;

motor leftFront = motor(PORT17, ratio18_1, false);
motor leftBack = motor(PORT18, ratio18_1, false);
motor center = motor(PORT16, ratio18_1, true);

motor rightFront = motor(PORT19, ratio18_1, true);
motor rightBack = motor(PORT20, ratio18_1, true);

motor_group leftGroup = motor_group(leftFront, leftBack);
motor_group rightGroup = motor_group(rightFront, rightBack);
motor_group centerGroup = motor_group(center);

motor mech = motor(PORT11, ratio18_1, false);
motor_group mechGroup = motor_group(mech);

void init(void) {
    Brain.Screen.clearScreen();
    chassis = new HDrive(12.5, 1.625, 1.625, &leftGroup, &rightGroup, &centerGroup, 1);
    chassis->setOffset(0, 3, 0);
    chassis->setBrakeType(brakeType::brake);
    chassis->setMaxAcceleration(2, 2);

    PID straight = PID(0.2, 0.65, 0.02);
    straight.setBias(0);
    straight.setMaxIntegral(8);
    straight.setLowSpeedThreshold(5);
    straight.setDelayTime(20);
    straight.setErrorRange(2);

    PID turn = PID(0.15, 0.7, 0.01);
    turn.setBias(0);
    turn.setMaxIntegral(8);
    turn.setLowSpeedThreshold(3);
    turn.setDelayTime(20);
    turn.setErrorRange(2);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);
    chassis->setMeasurementUnits(Conversion::measurement::in);

    PID strafe = PID(0.3, 0.67, 0.02);
    strafe.setBias(0);
    strafe.setMaxIntegral(10);
    strafe.setLowSpeedThreshold(5);
    strafe.setDelayTime(20);
    strafe.setErrorRange(2);

    chassis->setStrafePID(strafe);

    // Fourbar setup
    fourbar = new Mechanism(&mechGroup, 4);
    fourbar->setBrakeType(brakeType::hold);
    fourbar->setBounds(0, 90);
    fourbar->setBrakeType(hold);
    fourbar->setMaxAcceleration(5);
    fourbar->setOffset(0);

    PID lift = PID(1.5, 0.7, 0.02);
    fourbar->setPID(lift);

    LOG().setBaseLevel(DEBUG);
    LOG(INFO) << "Robot Initialized";
}