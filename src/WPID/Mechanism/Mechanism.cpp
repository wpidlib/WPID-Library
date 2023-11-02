#include "WPID/Mechanism/Mechanism.h"
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

void Mechanism::moveRelativeAsync(){}

void Mechanism::moveRelative(float position, float max_speed){
    float current = this->getPosition(deg);
    this->moveAbsolute(position + current, max_speed);
}

// Make moveAbsolute ASYNC first
// store targets and speeds in class
// set isMoving flag
// is settled call 
// delay intil is settled
void Mechanism::moveAbsoluteAsync(){}

void Mechanism::moveAbsolute(float position, float max_speed){
    float target = (position + offset);
    if(target > upper_bound){
        target = upper_bound;
    } else if (target < lower_bound) {
        target = lower_bound;
    }

    float state = 0;
    float error = 999;
    int calc = 0;
    float ramp = 0;

    //int startTime = (int)vex::timer::system();

    while(pid.cont(error)){
        //if((int)vex::timer::system() >= startTime + timeout) {break;}
        state = this->getPosition(rotationUnits::deg); // get the state of the motors
        error = target - state; // difference between target and state
        calc = pid.calculateSpeed(error, max_speed); // calculate PID speed for the left side
        
        if(error > target*(1 - MAX_RAMP_DURATION) && ramp <= max_speed && ramp > 0 && max_acceleration > 0) {
            calc = target < 0 ? 0.0 - ramp : ramp;
            ramp += max_acceleration;
        }

        std::cout << "Target: " << target << " State: " << state << " Error: " << error << " Speed: " << calc << std::endl;

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