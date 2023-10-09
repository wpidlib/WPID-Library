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
    if(leftEnc != nullptr && rightEnc != nullptr){
        leftEnc->resetRotation();
        rightEnc->resetRotation();
        return;
    } 
    left->resetPosition();
    right->resetPosition();
}

void Chassis::forward(float distance, int max_speed){
    float target = (distance / wheel_circumference) * 360.0;
    this->setTarget(target, target, max_speed, max_speed, this->pidStraight);
}

void Chassis::turn(int target_angle, int max_speed){
    float target = ((track_width/2)*((float)target_angle*M_PI/180)/wheel_circumference)*360;
    this->setTarget(target, -target, max_speed, max_speed, this->pidTurn);

}

float Chassis::arc(float x, float y, int max_speed){
    float theta = tan(x/y); // find the angle of the 
    float s = theta*y/sin(theta);
    float sl = theta > 0 ? s + track_width/2 : s - track_width;
    float sr = theta > 0 ? s - track_width/2 : s + track_width;
    this->setTarget(sl, sr, sl > sr ? max_speed : sl/sr, sr > sl ? max_speed : sr/sl, pidStraight);
    return theta;
}

void Chassis::arc(float r, int target_angle, int max_speed){
    float theta = (((float)target_angle*M_PI)/180);
    float sl = target_angle > 0 ? theta * (r + track_width/2) : theta * (r - track_width);
    float sr = target_angle > 0 ? theta * (r - track_width/2) : theta * (r + track_width);
    sl = (sl/wheel_circumference)*360;
    sr = (sr/wheel_circumference)*360;
    float lspd = (sl/sr)*(float)max_speed;
    float rspd = (sr/sl)*(float)max_speed;
    // left->spinTo(sl, rotationUnits::deg, lspd, velocityUnits::pct, false);
    // right->spinTo(sr, rotationUnits::deg, rspd, velocityUnits::pct, false);
    this->spin(lspd,rspd);
    delay(20000);
    //this->setTarget(sl, sr, max_speed, (sr/sl)*(float)max_speed, pidStraight);
}

void Chassis::setTarget(float left_target, float right_target, int l_max_spd, int r_max_spd, PID pid){
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
        
        delay(pid.delay_time); // delay by pid.delay_time milliseconds
    }
    debug ? LOG("Final Error L: " << left_error) : true;
    debug ? LOG("Final Error R: " << right_error) : true;
    pid.reset();
    this->stop();
}

float Chassis::leftEncoder(rotationUnits units){
    if(leftEnc != nullptr) {
        return leftEnc->position(units);
    }
    return left->position(units);
}

float Chassis::rightEncoder(rotationUnits units){
    if(rightEnc != nullptr){
        return rightEnc->position(units);
    }
    return right->position(units);
}

void Chassis::setEncoders(encoder* left, encoder* right){
    this->leftEnc = left;
    this->rightEnc = right;
}

void Chassis::setBrakeType(brakeType type){
    left->setStopping(type);
    right->setStopping(type);
}

void Chassis::stop(){
    left->stop();
    right->stop();
}

void Chassis::engage(int l, int r){
    // if(target_angle > 0){
    //     target_angle += turn_offset;
    //     this->engage(0, -1);
        
    // } else {
    //     target_angle -= turn_offset;
    //     this->engage(-1, 0);
    // }
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
    
