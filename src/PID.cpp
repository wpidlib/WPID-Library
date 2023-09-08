#include "main.h"
#include <algorithm>

PID::PID(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd) {}

float PID::calculateSpeed(float error, float max_speed){
    float integral = prev_integral + error*delay_time; // summation of error over time
    float derivative = (error - prev_error) / delay_time; // slope of error over time

    float speed = error*kp + integral*ki + derivative*kd + bias; // calculated speed

    // cap speed at max speed
    if(speed > max_speed){ speed = max_speed; }
    if(speed < -max_speed){speed = -max_speed;}

    // retain minimum speed
    if (speed < bias && speed > 0) { speed = bias; }
    if (speed > -bias && speed < 0) { speed = -bias; }

    prev_error = error;
    prev_integral = ki != 0 ? integral : 0; // 0 the prev_integral if ki is 0
    return speed;
}

void PID::setErrorRange(float bound){
    this->bound = bound;
}

bool PID::cont(float error){
    return std::abs(error) > bound ? true : false;
}

void PID::reset(void){
    prev_error = 0;
    prev_integral = 0;
}