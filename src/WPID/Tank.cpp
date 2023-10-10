#include "WPID/Tank.h"
using namespace vex;

Tank::Tank(float track_width, float wheel_radius, vex::motor_group* left, vex::motor_group* right){
    this->track_width = track_width;
    this->wheel_circumference = 2.0 * M_PI * wheel_radius;
    this->left = left;
    this->right = right;
}

void Tank::setStraightPID(PID pid){
    pidStraight = pid;
}

void Tank::setTurnPID(PID pid){
    pidTurn = pid;
}

void Tank::spin(int left_velocity, int right_velocity){
    left->spin(directionType::fwd, left_velocity, velocityUnits::pct);
    right->spin(directionType::fwd, right_velocity, velocityUnits::pct);
}

void Tank::spin(int velocity){
    this->spin(velocity, velocity);
}

void Tank::resetEncoders(){
    if(leftEnc != nullptr && rightEnc != nullptr){
        leftEnc->resetRotation();
        rightEnc->resetRotation();
        return;
    } 
    left->resetPosition();
    right->resetPosition();
}

void Tank::forward(float distance, int max_speed){
    float target = ((distance + straight_offset) / wheel_circumference) * 360.0;
    this->setTarget(target, target, max_speed, max_speed, this->pidStraight);
}

void Tank::turn(int target_angle, int max_speed){
    float target = ((track_width/2)*((float)(target_angle+turn_offset)*M_PI/180)/wheel_circumference)*360;
    this->setTarget(target, -target, max_speed, max_speed, this->pidTurn);
}

void Tank::setTarget(float left_target, float right_target, int l_max_spd, int r_max_spd, PID pid){
    this->resetEncoders();
    left_target += this->leftEncoder(rotationUnits::deg); // retains state
    right_target += this->rightEncoder(rotationUnits::deg); // retains state
    
    float left_error = 999;
    float right_error = 999; // make large to enter loop
    float left_state, right_state = 0;
    PID pidTemp = pid.copy(); //Creating a temporary PID object
   
    while(pid.cont(left_error) || pidTemp.cont(right_error)){
        left_state = leftEncoder(rotationUnits::deg); // get the state of the left side
        right_state = rightEncoder(rotationUnits::deg); // get the state of the right side

        left_error = left_target - left_state; // difference between target and state
        right_error = right_target - right_state; // difference between target and state

        int left_calc = pid.calculateSpeed(left_error, l_max_spd); // calculate PID speed for the left side
        int right_calc = pid.calculateSpeed(right_error, r_max_spd); // calculate PID speed for the right side
        
        this->spin(left_calc, right_calc); // spin the motors at speed
        
        wait(pid.delay_time, msec); // delay by pid.delay_time milliseconds
    }
    pid.reset();
    this->stop();
}

float Tank::leftEncoder(rotationUnits units){
    if(leftEnc != nullptr) {
        return leftEnc->position(units);
    }
    return left->position(units);
}

float Tank::rightEncoder(rotationUnits units){
    if(rightEnc != nullptr){
        return rightEnc->position(units);
    }
    return right->position(units);
}

void Tank::setEncoders(encoder* left, encoder* right){
    this->leftEnc = left;
    this->rightEnc = right;
}

void Tank::setBrakeType(brakeType type){
    left->setStopping(type);
    right->setStopping(type);
}

void Tank::setOffset(float straight, float turn){
    straight_offset = straight;
    turn_offset = turn;
}

void Tank::stop(){
    left->stop();
    right->stop();
}

void Tank::engage(int l, int r){
    double p = 30;
    left->spinTo(left->position(rotationUnits::raw) + l*p, rotationUnits::raw);
    right->spinTo(right->position(rotationUnits::raw) + r*p, rotationUnits::raw);
}


void ramp(){
    // int spd = 0;
    // int count = 0;
    // int half_speed = (int)fabs(pidStraight.calculateSpeed((error / 2), max_speed));
    // pidTurn.reset();
    // while(count != half_speed){
    //     spd = target > 0 ? count : -count;
    //     this->spin(-spd, spd);
    //     count++;
    //     delay(10);   
    // }
    // this->spin(-spd, spd);
}

void torque(){
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
} 
    
