#include "main.h"
#include <iostream>
#include <fstream>
using namespace std;

Chassis::Chassis(float track_width, float wheel_base, float wheel_radius, motor_group* left, motor_group* right) : wheel_base(wheel_base), track_width(track_width), left(left), right(right) {
    wheel_circumference = 2.0 * M_PI * wheel_radius;
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
    this->resetEncoders();

    float target = (distance / wheel_circumference) * 360.0;
    float error = target;
    float avg = 0;

    int count = 0;
    int half_speed = (int)fabs(pidStraight.calculateSpeed((error / 2), max_speed));
    pidStraight.reset();
    while(count != half_speed){
        this->spin(distance > 0 ? count : -count);
        count++;
        delay(10);
    }
    this->spin(distance > 0 ? max_speed : -max_speed);

    while (pidStraight.cont(error)) {
        avg = (leftEncoder(rotationUnits::deg) + rightEncoder(rotationUnits::deg)) / 2; 
        error = target - avg;
        int speed = pidStraight.calculateSpeed(error, max_speed);
        this->spin(speed);
        delay(pidStraight.delay_time);
    }
    debug ? LOG("Final Error: " << error) : true;
    pidStraight.reset();
    this->stop();
}

void Chassis::turn(float target_angle, int max_speed){
    if(target_angle > 0){
        target_angle += turn_offset;
        this->engage(-1, 0);
        
    } else {
        target_angle -= turn_offset;
        this->engage(0, -1);
    }
    this->resetEncoders();

    float r = (pow(wheel_base, 2) + pow(track_width, 2)) / (track_width * (wheel_circumference/M_PI));
    float target = (target_angle*M_PI*2*r) / wheel_circumference;
    float error = target;
    float avg = 0;

    int spd = 0;
    int count = 0;
    int half_speed = (int)fabs(pidStraight.calculateSpeed((error / 2), max_speed));
    pidTurn.reset();
    while(count != half_speed){
        spd = target > 0 ? count : -count;
        this->spin(-spd, spd);
        count++;
        delay(10);   
    }
    this->spin(-spd, spd);

    while(pidTurn.cont(error)){
        avg = (fabs(leftEncoder(rotationUnits::deg)) + fabs(rightEncoder(rotationUnits::deg))) / 2; 
        avg = target_angle < 0 ? -avg : avg;
        error = target - avg;
        int speed = pidTurn.calculateSpeed(error, max_speed);
        this->spin(-speed, speed);
        delay(pidTurn.delay_time);
    }
    debug ? LOG("Final Error: " << error) : true;
    pidTurn.reset();
    this->stop();
    if(target_angle > 0){
        this->engage(1, 0);
    } else {
        this->engage(0, 1);
    }
}

float Chassis::arc(float x, float y, float max_speed){
    float theta = tan(x/y);
    float s = theta*y/sin(theta);
    float sl = theta > 0 ? s + track_width/2 : s - track_width;
    float sr = theta > 0 ? s - track_width/2 : s + track_width;

    return theta;
}

float Chassis::leftEncoder(rotationUnits units){
    if(leftEnc != NULL) {
        return leftEnc->position(units);
    }
    return left->position(units);
}

float Chassis::rightEncoder(rotationUnits units){
    if(rightEnc != NULL){
        return rightEnc->position(units);
    }
    return right->position(units);
}

void Chassis::setBrakeType(brakeType type){
    left->setStopping(type);
    right->setStopping(type);
}

void Chassis::stop(){
    left->stop(brakeType::hold);
    right->stop(brakeType::hold);
}

void Chassis::engage(int l, int r){
    double p = 40;
    left->spinTo(left->position(rotationUnits::raw) + l*p, rotationUnits::raw);
    right->spinTo(right->position(rotationUnits::raw) + r*p, rotationUnits::raw);
}

    // int v = 650;
    // while(1){
    //     left->spin(directionType::fwd, v, voltageUnits::mV);
    //     right->spin(directionType::fwd, v, voltageUnits::mV);
    //     v += 10;
    //     LOG("V: " << v);
    //     LOG("LCurr: " << left->current() << " LTorq: " << left->torque() << " LPowr: " << left->power() << " LEff: " << left->efficiency());
    //     LOG("RCurr: " << right->current() << " RTorq: " << right->torque() << " RPowr: " << right->power() << " REff: " << right->efficiency());
    //     delay(2000);
    // }   
