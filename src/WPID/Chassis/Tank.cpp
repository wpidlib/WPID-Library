#include "WPID/Chassis/Tank.h"

using namespace vex;
using namespace wpid;

Tank::Tank(float track_width, float wheel_radius, vex::motor_group* left, vex::motor_group* right, float drive_gear_ratio){
    if(drive_gear_ratio <= 0)
        LOG(WARN) << "Cannot use a non-positive drive ratio";
    if(left->count() == 0)
        LOG(WARN) << "No motors found in \"LEFT\" motor group";
    if(right->count() == 0)
        LOG(WARN) << "No motors found in \"RIGHT\" motor group";
    
    this->track_width = track_width;
    this->wheel_circumference = 2.0 * M_PI * wheel_radius;

    this->left = new Mechanism(left, drive_gear_ratio,   "LEFT ");
    this->right = new Mechanism(right, drive_gear_ratio, "RIGHT");
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
    this->straightAsync(distance, max_speed);
    this->waitUntilSettled();
}

void Tank::straightAsync(float distance, int max_speed){
    distance = Conversion::standardize(distance, this->measure_units);
    float target = ((distance) / wheel_circumference) * 360.0;
    left->setPID(pidStraight.copy());
    right->setPID(pidStraight.copy());
    left->setOffset(straight_offset);
    right->setOffset(straight_offset);
    this->spinToTarget(target, target, max_speed, max_speed);
}

void Tank::turn(int target_angle, int max_speed){
    this->turnAsync(target_angle, max_speed);
    this->waitUntilSettled();
}

void Tank::turnAsync(float target_angle, int max_speed){
    float target = ((track_width/2)*((float)(target_angle)*M_PI/180)/wheel_circumference)*360;
    left->setPID(pidTurn.copy());
    right->setPID(pidTurn.copy());
    left->setOffset(turn_offset);
    right->setOffset(turn_offset);
    this->spinToTarget(target, -target, max_speed, max_speed);
}

void Tank::spinToTarget(float left_target, float right_target, int l_max_spd, int r_max_spd){    
    left->moveRelativeAsync(left_target, l_max_spd);
    right->moveRelativeAsync(right_target, r_max_spd);
}   

void Tank::stop(){
    left->stop();
    right->stop();
}

void Tank::waitUntilSettled(){
    this->left->waitUntilSettled();
    this->right->waitUntilSettled();
}

float Tank::getLeftPosition(rotationUnits units){
    return left->getPosition(units);
}

float Tank::getRightPosition(rotationUnits units){
    return right->getPosition(units);
}

void Tank::resetPosition(){
    left->resetPosition();
    right->resetPosition();
}

void Tank::setBrakeType(brakeType type){
    left->setBrakeType(type);
    right->setBrakeType(type);
}

void Tank::setOffset(float straight, float turn){
    straight_offset = ((straight) / wheel_circumference) * 360.0;
    turn_offset = ((track_width/2)*((float)(turn)*M_PI/180)/wheel_circumference)*360;
}

void Tank::setMaxAcceleration(float max_accel){
    if(max_accel < 0)
        LOG(WARN) << "Negative accelerations not allowed";
    this->left->setMaxAcceleration(max_accel);
    this->right->setMaxAcceleration(max_accel);
}

void Tank::setTimeout(int timeout){
    this->pidStraight.setTimeout(timeout);
    this->pidTurn.setTimeout(timeout);
}

void Tank::setMeasurementUnits(Conversion::measurement preferred_units){
    this->measure_units = preferred_units;
    this->wheel_circumference = Conversion::standardize(this->wheel_circumference, preferred_units);
    this->track_width = Conversion::standardize(this->track_width, preferred_units);
}
