#include "WPID/Mechanism/Mechanism.h"
using namespace vex;

Mechanism::Mechanism(motor_group* motors, float gear_ratio){
    this->motors = motors;
    this->gear_ratio = gear_ratio;
}

void Mechanism::spin(int velocity){
    motors->spin(directionType::fwd, velocity, velocityUnits::pct);
}

void Mechanism::stop(){
    motors->stop();
}

void Mechanism::setAngle(float angle, float max_speed){
    float target = angle / gear_ratio;
    this->resetPosition();
    target += this->getPosition(rotationUnits::deg); // retains state
    
    float error = 999;
    float state = 0;

    float ramp = 0;
    while(pid.cont(error)){
        state = this->getPosition(rotationUnits::deg); // get the state of the motors

        error = target - state; // difference between target and state

        int calc = pid.calculateSpeed(error, max_speed); // calculate PID speed for the left side
        
        if(error > target*.75 && ramp <= max_speed && ramp > 0) {
            calc = target < 0 ? 0.0-ramp : ramp;
            ramp += max_acceleration;
        }

        this->spin(calc); // spin the motors at speed
        wait(pid.delay_time, msec); // delay by pid.delay_time milliseconds
    }
    pid.reset();
    this->stop();
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