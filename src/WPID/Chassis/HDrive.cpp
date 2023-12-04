#include "WPID/Chassis/HDrive.h"

using namespace vex;
using namespace wpid;

HDrive::HDrive(float track_width, float wheel_radius, float center_wheel_radius, vex::motor_group* left, vex::motor_group* right, vex::motor_group* center, float drive_gear_ratio){
    if(drive_gear_ratio <= 0)
        LOG(WARN) << "Cannot use a non-positive drive ratio";
    if(left->count() == 0)
        LOG(WARN) << "No motors found in \"LEFT\" motor group";
    if(right->count() == 0)
        LOG(WARN) << "No motors found in \"RIGHT\" motor group";
    if(center->count() == 0)
        LOG(WARN) << "No motors found in \"CENTER\" motor group";

    
    this->track_width = track_width;
    this->wheel_circumference = 2.0 * M_PI * wheel_radius;
    this->center_wheel_circumference = 2.0 * M_PI * center_wheel_radius;

    this->left = new Mechanism(left, drive_gear_ratio, "LEFT");
    this->right = new Mechanism(right, drive_gear_ratio, "RIGHT");
    this->center = new Mechanism(center, drive_gear_ratio, "CENTER");
}


void HDrive::setStraightPID(PID pid){
    pidStraight = pid;
}

void HDrive::setTurnPID(PID pid){
    pidTurn = pid;
}

void HDrive::setStrafePID(PID pid){
    pidStrafe = pid;
    center->setPID(pidStrafe);
}

void HDrive::spin(int left_velocity, int right_velocity, int center_velocity){
    left->spin(left_velocity);
    right->spin(right_velocity);
    center->spin(center_velocity);
}

void HDrive::spin(int sides, int center){
    this->spin(sides, sides, center);
}

void HDrive::straight(float distance, int max_speed){
    this->straightAsync(distance, max_speed);
    this->waitUntilSettled();
}

void HDrive::straightAsync(float distance, int max_speed){
    distance = Conversion::standardize(distance, this->measure_units);
    if(distance > 0){
        distance += straight_offset;
    } else {
        distance -= straight_offset;
    }
    float target = ((distance) / wheel_circumference) * 360.0;
    left->setPID(pidStraight.copy());
    right->setPID(pidStraight.copy());
    this->spinToTarget(target, target, 0, max_speed, max_speed, 0);
}

void HDrive::turn(int target_angle, int max_speed){
    this->turnAsync(target_angle, max_speed);
    this->waitUntilSettled();
}

void HDrive::turnAsync(float target_angle, int max_speed){
    if(target_angle > 0){
        target_angle += turn_offset;
    } else {
        target_angle -= turn_offset;
    }
    float target = ((track_width/2)*((float)(target_angle)*M_PI/180)/wheel_circumference)*360;
    left->setPID(pidTurn.copy());
    right->setPID(pidTurn.copy());
    this->spinToTarget(target, -target, 0, max_speed, max_speed, 0);
}

void HDrive::strafe(float distance, int max_speed){
    this->strafeAsync(distance, max_speed);
    this->waitUntilSettled();
}

void HDrive::strafeAsync(float distance, int max_speed){
    distance = Conversion::standardize(distance, this->measure_units);
     if(distance > 0){
        distance += strafe_offset;
    } else {
        distance -= strafe_offset;
    }
    float target = ((distance) / center_wheel_circumference) * 360.0;
    this->spinToTarget(0, 0, target, 0, 0, max_speed);
}

void HDrive::diagonal(float straight_distance, float strafe_distance, int straight_max_speed){
    this->diagonalAsync(straight_distance, strafe_distance, straight_max_speed);
    this->waitUntilSettled();
}

void HDrive::diagonalAsync(float straight_distance, float strafe_distance, int straight_max_speed){
    straight_distance = Conversion::standardize(straight_distance, this->measure_units);
    strafe_distance = Conversion::standardize(strafe_distance, this->measure_units);
    float straight_target = ((straight_distance + straight_offset) / wheel_circumference) * 360.0;
    float strafe_target = ((strafe_distance + strafe_offset) / center_wheel_circumference) * 360.0;
    float center_max_speed = straight_max_speed*(strafe_distance / straight_distance);
    left->setPID(pidStraight);
    right->setPID(pidStraight);
    this->spinToTarget(straight_target, straight_target, strafe_target, straight_max_speed, straight_max_speed, center_max_speed);
}

void HDrive::spinToTarget(float left_target, float right_target, float center_target, int l_max_spd, int r_max_spd, int c_max_spd){
    left->moveRelativeAsync(left_target, l_max_spd);
    right->moveRelativeAsync(right_target, r_max_spd);
    center->moveRelativeAsync(center_target, c_max_spd);
}

void HDrive::stop(){
    left->stop();
    right->stop();
    center->stop();
}

void HDrive::waitUntilSettled(){
    this->left->waitUntilSettled();
    this->right->waitUntilSettled();
    this->center->waitUntilSettled();
}

float HDrive::getLeftPosition(rotationUnits units){
    return left->getPosition(units);
}

float HDrive::getRightPosition(rotationUnits units){
    return right->getPosition(units);
}

float HDrive::getCenterPosition(rotationUnits units){
    return center->getPosition(units);
}

void HDrive::resetPosition(){
    left->resetPosition();
    right->resetPosition();
    center->resetPosition();
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

void HDrive::setMaxAcceleration(float straight_max_accel, float c_max_accel){
    if(straight_max_accel < 0 || c_max_accel < 0)
        LOG(WARN) << "Negative accelerations not allowed";
    this->left->setMaxAcceleration(straight_max_accel);
    this->right->setMaxAcceleration(straight_max_accel);
    this->center->setMaxAcceleration(c_max_accel);
}

void HDrive::setTimeout(int timeout){
    this->pidStraight.setTimeout(timeout);
    this->pidTurn.setTimeout(timeout);
    this->pidStrafe.setTimeout(timeout);
}

void HDrive::setMeasurementUnits(Conversion::measurement preferred_units){
    this->measure_units = preferred_units;
    this->wheel_circumference = Conversion::standardize(this->wheel_circumference, preferred_units);
    this->track_width = Conversion::standardize(this->track_width, preferred_units);
}
