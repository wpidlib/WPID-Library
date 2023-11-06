#include "WPID/Mechanism/Mechanism.h"
#include <stdlib.h>
using namespace vex;

Mechanism::Mechanism(motor_group* motors, float gear_ratio){
    this->motors = motors;
    this->gear_ratio = gear_ratio;
}

void Mechanism::spin(int velocity){
    float position = this->getPosition(rotationUnits::deg);
    if((velocity > 0 && position < upper_bound)
    || (velocity < 0 && position > lower_bound)
    || (upper_bound == lower_bound)){
        motors->spin(directionType::fwd, velocity, velocityUnits::pct);
    } else {
        motors->stop();
    }
}

void Mechanism::stop(){
    motors->stop();
}

void Mechanism::waitUntilSettled(){
    while(!this->isSettled){
        wait(20, msec);
    }
}

void Mechanism::moveRelativeAsync(float position, float max_speed){
    float current = this->getPosition(deg);
    this->moveAbsoluteAsync(position + current, max_speed);
}

void Mechanism::moveRelative(float position, float max_speed){
    this->moveRelativeAsync(position, max_speed);
    this->waitUntilSettled();
}

void Mechanism::moveAbsoluteAsync(float position, float max_speed){
    isSettled = false;
    void* arg = (void*)getParams(position, max_speed);
    thread(setTarget, arg);
}

void Mechanism::moveAbsolute(float position, float max_speed){
    this->moveAbsoluteAsync(position, max_speed);
    this->waitUntilSettled();
}

void Mechanism::setTarget(void* args){
    params* input = (params*)args;
    Mechanism* mech = input->mech;
    float max_speed = input->spd;
    float target = (input->pos + mech->offset);
    // if(target > mech->upper_bound){
    //     target = mech->upper_bound;
    // } else if (target < mech->lower_bound) {
    //     target = mech->lower_bound;
    // }

    float state = 0;
    float error = 999;
    int calc = 0;
    float ramp = 0;

    //int startTime = (int)vex::timer::system();

    while(mech->pid.cont(error)){
        //if((int)vex::timer::system() >= startTime + timeout) {break;}
        state = mech->getPosition(rotationUnits::deg); // get the state of the motors
        error = target - state; // difference between target and state
        calc = mech->pid.calculateSpeed(error, max_speed); // calculate PID speed for the left side
        
        if(error > target*(1 - mech->MAX_RAMP_DURATION) && ramp <= max_speed && ramp > 0 && mech->max_acceleration > 0) {
            calc = target < 0 ? 0.0 - ramp : ramp;
            ramp += mech->max_acceleration;
        }

        mech->spin(calc); // spin the motors at speed
        wait(mech->pid.delay_time, msec); // delay by pid.delay_time milliseconds
    }
    mech->pid.reset();
    mech->stop();
    mech->isSettled = true;
}

float Mechanism::getPosition(rotationUnits units){
    return motors->position(units) * gear_ratio;
}

void Mechanism::resetPosition(){
    motors->resetPosition();
}

void Mechanism::setBrakeType(brakeType type){
    motors->setStopping(type);
}

void Mechanism::setPID(PID pid){
    this->pid = pid;
}

void Mechanism::setOffset(float offset){
    this->offset = offset;
}

void Mechanism::setMaxAcceleration(float max_accel){
    this->max_acceleration = max_accel;
}

void Mechanism::setBounds(float lower_bound, float upper_bound){
    this->lower_bound = lower_bound;
    this->upper_bound = upper_bound;
}

void Mechanism::setTimeout(int timeout){
    this->timeout = timeout;
}

void Mechanism::setName(char* name){
    std::string t = std::string(name);
    this->name = t;
}
