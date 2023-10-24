#include "WPID/Chassis/HDrive.h"

HDrive::HDrive(float track_width, float wheel_radius, float center_wheel_radius, vex::motor_group* left, vex::motor_group* right, vex::motor_group* center){
    this->track_width = track_width;
    this->wheel_circumference = 2.0 * M_PI * wheel_radius;
    this->center_wheel_circumference = 2.0 * M_PI * center_wheel_radius;
    this->left = left;
    this->right = right;
    this->center = center;
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
    left->spin(directionType::fwd, left_velocity, velocityUnits::pct);
    right->spin(directionType::fwd, right_velocity, velocityUnits::pct);
    center->spin(directionType::fwd, center_velocity, velocityUnits::pct);
}

void HDrive::spin(int velocity){
    this->spin(velocity, velocity, 0);
}

void HDrive::resetEncoders(){
    if(leftEnc != nullptr && rightEnc != nullptr){
        leftEnc->resetRotation();
        rightEnc->resetRotation();
        centerEnc->resetRotation();
        return;
    } 
    left->resetPosition();
    right->resetPosition();
    center->resetPosition();
}

void HDrive::straight(float distance, int max_speed){
    float target = ((distance + straight_offset) / wheel_circumference) * 360.0;
    this->setTarget(target, target, 0, max_speed, max_speed, 0, this->pidStraight);
}

void HDrive::turn(int target_angle, int max_speed){
    float target = ((track_width/2)*((float)(target_angle+turn_offset)*M_PI/180)/wheel_circumference)*360;
    this->setTarget(target, -target, 0, max_speed, max_speed, 0, this->pidTurn);
}

void HDrive::strafe(float distance, int max_speed){
    float target = ((distance + strafe_offset) / center_wheel_circumference) * 360.0;
    this->setTarget(0, 0, target, 0, 0, max_speed, this->pidStrafe);
}

void HDrive::diagonal(float straight_distance, float strafe_distance, int straight_max_speed){
    float straight_target = ((straight_distance + straight_offset) / wheel_circumference) * 360.0;
    float strafe_target = ((strafe_distance + strafe_offset) / center_wheel_circumference) * 360.0;
    float center_max_speed = straight_max_speed*(strafe_distance / straight_distance);
    this->setTarget(straight_target, straight_target, strafe_target, straight_max_speed, straight_max_speed, center_max_speed, this->pidStraight);
}

void HDrive::setTarget(float left_target, float right_target, float center_target, int l_max_spd, int r_max_spd, int c_max_spd, PID pid){
    this->resetEncoders();
    left_target += this->leftEncoder(rotationUnits::deg); // retains state
    right_target += this->rightEncoder(rotationUnits::deg); // retains state
    center_target += this->centerEncoder(rotationUnits::deg); // retains state

    float left_error = 999;
    float right_error = 999; // make large to enter loop
    float center_error = 999;
    float left_state, right_state, center_state = 0;
    PID pidTemp = pid.copy(); //Creating a temporary PID object

    float ramp = 0;
    float center_ramp = 0;
    while(pid.cont(left_error) || pidTemp.cont(right_error) || pidStrafe.cont(center_error)){
        left_state = leftEncoder(rotationUnits::deg); // get the state of the left side
        right_state = rightEncoder(rotationUnits::deg); // get the state of the right side
        center_state = centerEncoder(rotationUnits::deg); // get the state of the center wheel

        left_error = left_target - left_state; // difference between target and state
        right_error = right_target - right_state; // difference between target and state
        center_error = center_target - center_state; //

        int left_calc = pid.calculateSpeed(left_error, l_max_spd); // calculate PID speed for the left side
        int right_calc = pidTemp.calculateSpeed(right_error, r_max_spd); // calculate PID speed for the right side
        int center_calc = pidStrafe.calculateSpeed(center_error, c_max_spd); // calculate PID speed for the center wheel

        if(left_error > left_target*.75 && ramp < l_max_spd && ramp > 0) {
            left_calc = left_target < 0 ? 0.0-ramp : ramp;
            right_calc = right_target < 0 ? 0.0-ramp : ramp;
            ramp += max_acceleration;
        }

        if(center_error > center_target*.75 && center_ramp < c_max_spd && center_ramp > 0){
            center_calc = center_target < 0 ? 0.0-ramp : ramp;
            center_ramp += max_acceleration;
        }

        this->spin(left_calc, right_calc, center_calc); // spin the motors at speed
        wait(pid.delay_time, msec); // delay by pid.delay_time milliseconds
    }
    pid.reset();
    this->stop();
}

float HDrive::leftEncoder(rotationUnits units){
    if(leftEnc != nullptr) {
        return leftEnc->position(units);
    }
    return left->position(units);
}

float HDrive::rightEncoder(rotationUnits units){
    if(rightEnc != nullptr){
        return rightEnc->position(units);
    }
    return right->position(units);
}

float HDrive::centerEncoder(rotationUnits units){
    if(centerEnc != nullptr){
        return centerEnc->position(units);
    }
    return center->position(units);
}

void HDrive::setEncoders(encoder* left, encoder* right, encoder* center){
    this->leftEnc = left;
    this->rightEnc = right;
    this->centerEnc = center;
}

void HDrive::setBrakeType(brakeType type){
    left->setStopping(type);
    right->setStopping(type);
    center->setStopping(type);
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