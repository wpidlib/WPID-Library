#include "main.h"

Chassis::Chassis(float wheel_base, float wheel_radius, motor_group* left, motor_group* right) : wheel_base(wheel_base), wheel_radius(wheel_radius), left(left), right(right)
{
    //Wheel_Circumference: Inches
    wheel_circumference = 2 * M_PI * wheel_radius;
    pid = PID(1,1,1); 
}

bool evalDir(int port){
    return port < 0 ? true : false;
}

/*
basic move forward function
*/

void Chassis::spin(int left_velocity, int right_velocity){
    left->spin(directionType::fwd, left_velocity, velocityUnits::pct);
    right->spin(directionType::fwd, right_velocity, velocityUnits::pct);
}
void Chassis::spin(int max_velocity){
    this->spin(max_velocity, max_velocity);
}

void Chassis::forward(float distance, int max_velocity){
    // while(PID.continue()){
    //     PID.update();
    //     this->spin(PID.velocity());
    // }
}

void Chassis::turn(float target_angle, int max_velocity){
    // Arc_Length: Inches
    float arc_length = (target_angle / 360) * wheel_base * M_PI;
    
    // while(PID.continue()){
    //     PID.update();
    //     this->spin(PID.velocity());
    // }
}

float Chassis::getEncoderCount(){}