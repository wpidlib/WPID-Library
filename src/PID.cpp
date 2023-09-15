#include "main.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

PID::PID(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd) {}

float PID::calculateSpeed(float error, float max_speed){
    float integral = prev_integral + (error * (delay_time/(float)1000)); // summation of error over time
    if(fabs(integral) > max_integral) { 
        integral = integral > 0 ? max_integral : -max_integral;
    }

    float derivative = (error - prev_error) / (delay_time/(float)1000); // slope of error over time

    float speed = error*kp + integral*ki + (-1.0)*derivative*kd + bias; // calculated speed

    // cap speed at max speed
    if(speed > max_speed){ speed = max_speed; }
    if(speed < -max_speed){ speed = -max_speed; }

    // retain minimum speed
    if (speed < bias && speed > 0) { speed = bias; }
    if (speed > -bias && speed < 0) { speed = -bias; }

    prev_error = error;
    prev_integral = ki != 0 ? integral : 0; // 0 the prev_integral if ki is 0

    //std::cout << round(error*100.0)/100.0 << "," << round(speed*100.0)/100.0 << "," << round(integral*100.0)/100.0 << "," << round(derivative*100.0)/100.0 << std::endl;
    LOG("Error:    " << error);
    LOG("Speed:    " << speed);
    LOG("Prop:     " << error*kp);
    LOG("Integ:    " << integral);
    LOG("Deriv:    " << derivative);
    return speed;
}

void PID::setErrorRange(float bound){
    this->bound = bound;
}

bool PID::cont(float error){
    return std::fabs(error) > bound ? true : false;
}

void PID::reset(void){
    prev_error = 0;
    prev_integral = 0;
}