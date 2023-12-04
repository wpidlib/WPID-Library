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
    chassis->setOffset(0, 5);
    chassis->setBrakeType(brakeType::brake);
    chassis->setMaxAcceleration(2);

    PID straight = PID(0.2, 0.65, 0.02);
    straight.setBias(0);
    straight.setMaxIntegral(8);
    straight.setLowSpeedThreshold(5);
    straight.setDelayTime(20);
    straight.setErrorRange(2);

    PID turn = PID(0.15, 0.65, 0.02);
    turn.setBias(0);
    turn.setMaxIntegral(8);
    turn.setLowSpeedThreshold(3);
    turn.setDelayTime(20);
    turn.setErrorRange(2);

    chassis->setStraightPID(straight);
    chassis->setTurnPID(turn);

    // Fourbar setup
    fourbar = new Mechanism(&mechGroup, 0.25);
    fourbar->setBrakeType(brakeType::hold);
    fourbar->setMaxAcceleration(5);
    fourbar->setBounds(0, 110);

    PID lift = PID(1.3, 0.7, 0.02);
    fourbar->setPID(lift);

    LOG().setBaseLevel(DEBUG);
    LOG(INFO) << "Robot Initialized";
}