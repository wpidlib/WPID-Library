#include "main.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

PID::PID(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd) {}

//std::cout << round(error*100.0)/100.0 << "," << round(speed*100.0)/100.0 << "," << round(integral*100.0)/100.0 << "," << round(derivative*100.0)/100.0 << std::endl;
float PID::calculateSpeed(float error, float max_speed){
    // summation of error over time
    float integral = prev_integral + (error * (delay_time/(float)1000));

    // slope of error over time
    float derivative = (error - prev_error) / (delay_time/(float)1000); 
    prev_error = error; // set previous error to current error

    // calculated speed value
    float speed = error*kp + integral*ki + derivative*kd; // calculated speed
    float pre_speed = speed; // pre cap speed

    // cap speed at max speed if saturated (speed unobtainable)
    if(speed > max_speed){ speed = max_speed; }
    if(speed < -max_speed){ speed = -max_speed; }
    
    // if saturated, check if getting worse, if so then remove integral term
    // and dont add new integral to integral
    // basically only starts to integrate if our output is less than our maximum
    if(speed != pre_speed && signbit(error) == signbit(pre_speed)){
        speed -= integral*ki;
        integral = prev_integral;
        speed += integral*ki;
    } // integral clamping
    prev_integral = integral;

    // retain minimum speed
    if (speed < bias && speed > 0) { speed = bias; }
    if (speed > -bias && speed < 0) { speed = -bias; }

    std::cout << std::fixed << std::setprecision(2);
    LOG("| " << error << " | " << speed << " | " << error*kp << " | " << integral*ki << " | " << derivative*kd << " |"); 
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