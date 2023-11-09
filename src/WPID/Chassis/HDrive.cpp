#include "WPID/Chassis/HDrive.h"

using namespace wpid;

HDrive::HDrive(float track_width, float wheel_radius, float center_wheel_radius, vex::motor_group* left, vex::motor_group* right, vex::motor_group* center, float drive_gear_ratio){
    this->track_width = track_width;
    this->wheel_circumference = 2.0 * M_PI * wheel_radius;
    this->center_wheel_circumference = 2.0 * M_PI * center_wheel_radius;
    this->left = new Mechanism(left, drive_gear_ratio);
    this->right = new Mechanism(right, drive_gear_ratio);
    this->center = new Mechanism(center, drive_gear_ratio);
    this->center->setPID(pidStrafe);
}

void HDrive::setStraightPID(PID pid){
    pidStraight = pid;
}

void HDrive::setTurnPID(PID pid){
    pidTurn = pid;
}

void HDrive::setStrafePID(PID pid){
    pidStrafe = pid;
}

void HDrive::spin(int left_velocity, int right_velocity, int center_velocity){
    left->spin(left_velocity);
    right->spin(right_velocity);
    center->spin(center_velocity);
}

void HDrive::spin(int sides, int center){
    this->spin(sides, sides, center);
}

void HDrive::resetEncoders(){
    left->resetPosition();
    right->resetPosition();
    center->resetPosition();
}

void HDrive::straight(float distance, int max_speed){
    this->straightAsync(distance, max_speed);
    this->waitUntilSettled();
}

void HDrive::straightAsync(float distance, int max_speed){
    float target = ((distance + straight_offset) / wheel_circumference) * 360.0;
    left->setPID(pidStraight);
    right->setPID(pidStraight);
    this->setTarget(target, target, 0, max_speed, max_speed, 0);
}

void HDrive::turn(int target_angle, int max_speed){
    this->turnAsync(target_angle, max_speed);
    this->waitUntilSettled();
}

void HDrive::turnAsync(float target_angle, int max_speed){
    float target = ((track_width/2)*((float)(target_angle+turn_offset)*M_PI/180)/wheel_circumference)*360;
    left->setPID(pidTurn);
    right->setPID(pidTurn);
    this->setTarget(target, -target, 0, max_speed, max_speed, 0);
}

void HDrive::strafe(float distance, int max_speed){
    this->strafeAsync(distance, max_speed);
    this->waitUntilSettled();
}

void HDrive::strafeAsync(float distance, int max_speed){
    float target = ((distance + strafe_offset) / center_wheel_circumference) * 360.0;
    this->setTarget(0, 0, target, 0, 0, max_speed);
}

void HDrive::diagonal(float straight_distance, float strafe_distance, int straight_max_speed){
    this->diagonalAsync(straight_distance, strafe_distance, straight_max_speed);
    this->waitUntilSettled();
}

void HDrive::diagonalAsync(float straight_distance, float strafe_distance, int straight_max_speed){
    float straight_target = ((straight_distance + straight_offset) / wheel_circumference) * 360.0;
    float strafe_target = ((strafe_distance + strafe_offset) / center_wheel_circumference) * 360.0;
    float center_max_speed = straight_max_speed*(strafe_distance / straight_distance);
    left->setPID(pidStraight);
    right->setPID(pidStraight);
    this->setTarget(straight_target, straight_target, strafe_target, straight_max_speed, straight_max_speed, center_max_speed);
}

void HDrive::setTarget(float left_target, float right_target, float center_target, int l_max_spd, int r_max_spd, int c_max_spd){
    left->moveRelative(left_target, l_max_spd);
    right->moveRelative(right_target, r_max_spd);
    center->moveRelative(center_target, c_max_spd);
}

float HDrive::leftEncoder(rotationUnits units){
    return left->getPosition(units);
}

float HDrive::rightEncoder(rotationUnits units){
    return right->getPosition(units);
}

float HDrive::centerEncoder(rotationUnits units){
    return center->getPosition(units);
}

void HDrive::setBrakeType(brakeType type){
    left->setBrakeType(type);
    right->setBrakeType(type);
    center->setBrakeType(type);
}

void HDrive::setOffset(float straight, float turn, float center){
    straight_offset = straight;
    turn_offset = turn;
    strafe_offset = center;
}

void HDrive::stop(){
    left->stop();
    right->stop();
    center->stop();
}

void HDrive::setMaxAcceleration(float max_accel){
    this->max_acceleration = max_accel;
}

void HDrive::waitUntilSettled(){
    while(!this->left->isSettled && !this->right->isSettled && !this->center->isSettled){
        wait(20, msec);
    }
}