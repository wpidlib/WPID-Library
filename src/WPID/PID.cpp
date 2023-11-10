#include "WPID/PID.h"

float PID::calculateSpeed(float error, float max_speed){
    // summation of error over time
    float integral = prev_integral + (error * (delay_time/(float)1000));

    // slope of error over time
    float derivative = (error - prev_error) / (delay_time/(float)1000); 
    prev_error = error; // set previous error to current error

    // calculated speed value
    float speed = error*kp + integral*ki + derivative*kd; // calculated speed
    float prev_speed = speed; // pre cap speed
    
    // if saturated, check if getting worse
    // if getting worse, use previous integral and stop integrating
    // only starts to integrate if our output is less than our maximum
    if(speed != prev_speed && std::signbit(error) == std::signbit(prev_speed)){
        speed -= integral*ki;
        integral = prev_integral;
        speed += integral*ki;
    } // integral clamping
    prev_integral = integral;

    // cap speed at max speed if saturated
    if(speed > max_speed){ speed = max_speed; }
    if(speed < -max_speed){ speed = -max_speed; }

    // retain minimum speed
    if (speed < bias && speed > 0) { speed = bias; }
    if (speed > -bias && speed < 0) { speed = -bias; }

    return speed;
}

void PID::setErrorRange(float bound){
    this->bound = bound;
}

bool PID::cont(float error){
    return std::fabs(error) > bound ? true : false;
}

void PID::reset(void){
    prev_error = MAXFLOAT;
    prev_integral = 0;
}
