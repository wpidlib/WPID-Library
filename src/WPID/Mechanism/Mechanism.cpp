#include "WPID/Mechanism/Mechanism.h"
#include <stdlib.h>

using namespace vex;
using namespace wpid;

Mechanism::Mechanism(motor_group motors, float gear_ratio, std::string mech_id){
    this->motors = &motors;
    this->gear_ratio = gear_ratio;
    this->mech_id = mech_id;
}

Mechanism::Mechanism(motor_group motors, float gear_ratio){
    this->motors = &motors;
    this->gear_ratio = gear_ratio;
    this->mech_id = "MECHANISM";
}

void Mechanism::spin(int velocity){
    float position = this->getPosition(rotationUnits::deg);
    if((velocity > 0 && position < upper_bound)
    || (velocity < 0 && position > lower_bound)){
        motors->spin(directionType::fwd, velocity, velocityUnits::pct);
    } else {
        motors->stop();
    }
}

void Mechanism::stop(){
    motors->stop();
}

void Mechanism::waitUntilSettled(){
    this->mech_thread->join();
    delete(this->mech_thread);
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
    void* arg = (void*)getParams(position, max_speed);
    this->mech_thread = new thread(spinToTarget, arg);
}

void Mechanism::moveAbsolute(float position, float max_speed){
    this->moveAbsoluteAsync(position, max_speed);
    this->waitUntilSettled();
}

void Mechanism::spinToTarget(void* args){
    params* input = (params*)args;
    Mechanism* mech = input->mech;
    float max_speed = fabs(input->spd); // make sure max_speed is a scalar
    float target = input->pos + mech->offset;
    if(input->pos < 0) {
        target = input->pos - mech->offset;
    }

    //limit target to bounds if calcluations exceed bounds
    if(target > mech->upper_bound){
        target = mech->upper_bound;
        LOG(WARN) << mech->mech_id << "'s upper bound was exceeded, reduced to " << mech->upper_bound;
    } else if (target < mech->lower_bound) {
        target = mech->lower_bound;
        LOG(WARN) << mech->mech_id << "'s lower bound was exceeded, reduced to " << mech->lower_bound;
    }

    LOG(DEBUG) << "moving " << mech->mech_id << " to " << target << " with max speed " << max_speed;

    float state = 0;
    float error = 999;
    float ramp = 0;
    int calculated_speed = 999;
    int final_speed;

    while(mech->pid.unfinished(error, calculated_speed)){ // checks if the system is within bounds, low speed, or timed out
        state = mech->getPosition(rotationUnits::deg); // get the state of the motors
        error = target - state; // difference between target and state
       
        calculated_speed = mech->pid.calculateSpeed(error, max_speed, mech->mech_id); // calculate PID speed
        
        //limit to ramp speed if ramp is less than max_speed
        if(mech->max_acceleration > 0 && fabs(ramp) < max_speed){
            final_speed = ramp;
            ramp += error < 0 ? -mech->max_acceleration : mech->max_acceleration;
        } else {
            final_speed = calculated_speed;
        }

        mech->motors->spin(fwd, final_speed, pct); // spin the motors at speed
        this_thread::sleep_for(mech->pid.getDelayTime()); // delay by pid.delay_time milliseconds
    }

    LOG(DEBUG) << "Stopping " << mech->mech_id << " with " << error << " error";
    mech->stop();
    mech->pid.reset();
    return;
}

float Mechanism::getPosition(rotationUnits units){
    return motors->position(units) / gear_ratio;
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
    if(lower_bound >= upper_bound)
        LOG(WARN) << "Bounds might be reversed. Double check.";
    this->lower_bound = lower_bound;
    this->upper_bound = upper_bound;
}
