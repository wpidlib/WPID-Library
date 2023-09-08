#include "main.h"
#include <iostream>

Chassis::Chassis(float wheel_base, float wheel_radius, motor_group* left, motor_group* right) : wheel_base(wheel_base), left(left), right(right) {
    wheel_circumference = 2 * M_PI * wheel_radius;
    pidStraight = PID(0, 0, 0); 
    pidTurn = PID(0, 0, 0);
}

void Chassis::setStraightPID(PID pid){
    pidStraight = pid;
}

void Chassis::setTurnPID(PID pid){
    pidTurn = pid;
}

void Chassis::spin(int left_speed, int right_speed){
    left->spin(directionType::fwd, left_speed, velocityUnits::pct);
    right->spin(directionType::fwd, right_speed, velocityUnits::pct);
}

void Chassis::spin(int max_speed){
    this->spin(max_speed, max_speed);
}

void Chassis::resetEncoders(){
    left->resetPosition();
    right->resetPosition();
}

void Chassis::forward(float distance, int max_speed){
    this->engage();
    this->resetEncoders();
    float target = (distance / wheel_circumference) * 360;
    float error = target;
    float avg = 0;

    while (pidStraight.cont(error)) {
        debug ? LOG("Error: " << error) : true;

        avg = (leftEncoder(rotationUnits::deg) + rightEncoder(rotationUnits::deg)) / 2; 
        error = target - avg;
        int speed = pidStraight.calculateSpeed(error, max_speed);
        this->spin(speed);
        delay(pidStraight.delay_time);
    }
    this->stop();
}

void Chassis::turn(float target_angle, int max_speed){
    this->engage();
    this->resetEncoders();
    float target = (wheel_base * M_PI * target_angle) / wheel_circumference;
    float error = target;
    float avg = 0;
    
    while(pidTurn.cont(error)){
        debug ? LOG("Error: " << error) : true;

        avg = (fabs(leftEncoder(rotationUnits::deg)) + fabs(rightEncoder(rotationUnits::deg))) / 2; 
        avg = target_angle < 0 ? -avg : avg;
        error = target - avg;
        int speed = pidTurn.calculateSpeed(error, max_speed);
        this->spin(-speed, speed);
        delay(pidTurn.delay_time);
    }
    this->stop();
}

float Chassis::leftEncoder(rotationUnits units){
    return left->position(units);
}

float Chassis::rightEncoder(rotationUnits units){
    return right->position(units);
}


void Chassis::setBrakeType(brakeType type){
    left->setStopping(type);
    right->setStopping(type);
}

void Chassis::stop(){
    spin(0);
}

void Chassis::engage(){
    this->spin(2);
    delay(250);
    this->stop();
}