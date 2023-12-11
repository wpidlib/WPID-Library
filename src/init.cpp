#include "init.h"

brain Brain;
controller con = controller(controllerType::primary);

//Mechanism* fourbar;

motor leftFront = motor(PORT17, ratio18_1, false);
motor leftBack = motor(PORT18, ratio18_1, false);
motor center = motor(PORT16, ratio18_1, true);

motor rightFront = motor(PORT19, ratio18_1, true);
motor rightBack = motor(PORT20, ratio18_1, true);

motor_group leftGroup = motor_group(leftFront, leftBack);
motor_group rightGroup = motor_group(rightFront, rightBack);
motor_group centerGroup = motor_group(center);

// motor mech = motor(PORT11, ratio18_1, false);
// motor_group mechGroup = motor_group(mech);

HDrive chassis = HDrive(12.5, 1.625, 1.625, leftGroup, rightGroup, centerGroup, 1);

// Mechanism fourbar = Mechanism(mechGroup, 4);

void init(void) {
    LOG().setBaseLevel(DEBUG);
    Brain.Screen.clearScreen();

    LOG(DEBUG) << "HDrive";
    chassis.setOffset(0, 3, 0);
    chassis.setBrakeType(brakeType::brake);
    chassis.setMaxAcceleration(2, 2);

    LOG(DEBUG) << "PID Straight";
    //PID straight = PID(0.15, 0.025, 0.015);
    PID straight = PID(0.15, 0.025, 0.015);
    straight.setLowSpeedThreshold(5);
    straight.setMaxIntegral(8);
    straight.setErrorRange(2);

    LOG(DEBUG) << "PID turn";
    PID turn = PID(0.15, 0.05, 0.01);
    turn.setMaxIntegral(8);
    turn.setLowSpeedThreshold(3);
    turn.setErrorRange(2);

    LOG(DEBUG) << "PID strafe";
    PID strafe = PID(0.3, 0.67, 0.02);
    strafe.setMaxIntegral(10);
    strafe.setLowSpeedThreshold(5);
    strafe.setErrorRange(2);

    LOG(DEBUG) << "setting PID";
    chassis.setStraightPID(straight);
    chassis.setTurnPID(turn);
    chassis.setStrafePID(strafe);
    LOG(DEBUG) << "setting measurements";
    chassis.setMeasurementUnits(Conversion::measurement::in);

    // Fourbar setup
    // fourbar.setBrakeType(brakeType::hold);
    // fourbar.setBounds(0, 90);
    // fourbar.setMaxAcceleration(5);
    // fourbar.setOffset(0);

    // PID lift = PID(1.5, 0.7, 0.02);
    // fourbar.setPID(lift);

    LOG(INFO) << "Robot Initialized";
}