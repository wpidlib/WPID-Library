#include "WPID/Chassis/Tank.h"
using namespace vex;
using namespace wpid;
Tank::Tank(float track_width, float wheel_radius, vex::motor_group* left, vex::motor_group* right, float drive_gear_ratio){
    this->track_width = track_width;
    this->wheel_circumference = 2.0 * M_PI * wheel_radius;
    this->left = new Mechanism(left, drive_gear_ratio);
    this->right = new Mechanism(right, drive_gear_ratio);
}

void Tank::setStraightPID(PID pid){
    pidStraight = pid;
}

void Tank::setTurnPID(PID pid){
    pidTurn = pid;
}

void Tank::spin(int left_velocity, int right_velocity){
    left->spin(left_velocity);
    right->spin(right_velocity);
}

void Tank::spin(int velocity){
    this->spin(velocity, velocity);
}

void Tank::straight(float distance, int max_speed){
    float target = ((distance + straight_offset) / wheel_circumference) * 360.0;
    left->setPID(pidStraight);
    right->setPID(pidStraight);
    this->setTarget(target, target, max_speed, max_speed);
}

void Tank::turn(int target_angle, int max_speed){
    float target = ((track_width/2)*((float)(target_angle+turn_offset)*M_PI/180)/wheel_circumference)*360;
    left->setPID(pidTurn);
    right->setPID(pidTurn);
    this->setTarget(target, -target, max_speed, max_speed);
}

void Tank::setTarget(float left_target, float right_target, int l_max_spd, int r_max_spd){    
    left->moveRelative(left_target, l_max_spd);
    right->moveRelative(right_target, r_max_spd);
}   

float Tank::leftEncoder(rotationUnits units){
    return left->getPosition(units);
}

float Tank::rightEncoder(rotationUnits units){
    return right->getPosition(units);
}

void Tank::resetEncoders(){
    left->resetPosition();
    right->resetPosition();
}

void Tank::setBrakeType(brakeType type){
    left->setBrakeType(type);
    right->setBrakeType(type);
}

void Tank::setOffset(float straight, float turn){
    straight_offset = straight;
    turn_offset = turn;
}

void Tank::stop(){
    left->stop();
    right->stop();
}

void Tank::setMaxAcceleration(float max_accel){
    this->max_acceleration = max_accel;
}

void Tank::setName(char* name){
    std::string t = std::string(name);
    this->name = t;
}