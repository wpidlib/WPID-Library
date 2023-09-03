#include "main.h"

Chassis::Chassis(float wheel_base, float wheel_radius, int motorL[], int motorR[]) : wheel_base(wheel_base), wheel_radius(wheel_radius)
{
    //Wheel_Circumference: Inches
    wheel_circumference = 2 * M_PI * wheel_radius;

    num_motors = sizeof(motorL)/sizeof(motorL[0]);
    
    // left array setup
    left = (motor**)malloc(sizeof(motor*)*num_motors);
    for (size_t i = 0; i < num_motors; i++) {
        left[i] = new motor(motorL[i], false);
        right[i] = new motor(motorR[i], true);
    }   
    pid = PID(1,1,1); 
}

void Chassis::setSideVelocity(float speed, char side){
    motor** group = side == 'l' ? left : right;
    motor* m;
    for (int i = 0; i < num_motors; i++){
        m = *(group + i);
        m->spin(directionType::fwd, 100, velocityUnits::pct);
    }
}

void Chassis::forward(float distance, float max_velocity){
    float target_rev = distance/wheel_circumference;
    float dist_to_target;

    setSideVelocity(max_velocity, 'r');
    setSideVelocity(max_velocity, 'l');

    while(target_rev > getEncoderCount()){
        dist_to_target = target_rev - getEncoderCount();
        setSideVelocity(pid.updateVelocity(dist_to_target), 'r');
        setSideVelocity(pid.updateVelocity(dist_to_target), 'l');
    }
}

void Chassis::turn(float target_angle, float max_velocity){
    // Turn_Circumference: Degrees
    float turn_circumference = wheel_base * M_PI;
    // Arc_Length: Inches
    float arc_length = (target_angle / 360) * turn_circumference;
    
    //To be continued
}

float Chassis::getEncoderCount(){}