#include "main.h"
#include <iostream>

Chassis::Chassis(float wheel_base, float wheel_radius, motor_group* left, motor_group* right) : wheel_base(wheel_base), wheel_radius(wheel_radius), left(left), right(right)
{
    //Wheel_Circumference: Inches
    wheel_circumference = 2 * M_PI * wheel_radius;
    pidStraight = PID(0.2,0,0); 
    pidTurn = PID(2, 0, 0);
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

//Distance in inches
void Chassis::forward(float distance, int max_velocity){
    float diff = (distance / wheel_circumference) * 360;
    left->resetPosition();
    right->resetPosition();
    float avg = 0;
    float prevAvg = 0;
    while (fabs(diff) >= 3) {
        avg = (leftEncoder(rotationUnits::deg) + rightEncoder(rotationUnits::deg)) / 2; 
        //std::cout << avg << ", " << diff << ", " << wheel_circumference << std::endl;
        int speed = pidStraight.updateVelocity(diff, max_velocity);

        std::cout << "Speed: " << speed << std::endl;
        std::cout << "Avg: " << avg << std::endl;

        this->spin(speed);
        diff -= (avg - prevAvg);
        prevAvg = avg;
        delay(20);
    }
    this->stop();
}


// CCW + / CW -
void Chassis::turn(float target_angle, int max_velocity){
    // Diff is in degrees
    float diff = (wheel_base * M_PI * target_angle) / wheel_circumference;
    left->resetPosition();
    right->resetPosition();
    
    float avg = 0;
    float prevAvg = 0;

    if(target_angle < 0){diff = -diff;}
    
    while(fabs(diff) >= 3){

        int speed = pidTurn.updateVelocity(diff, max_velocity);

        if(target_angle < 0){
            avg = (leftEncoder(rotationUnits::deg) - rightEncoder(rotationUnits::deg)) / 2;
        }else{
            avg =  (rightEncoder(rotationUnits::deg) - leftEncoder(rotationUnits::deg)) / 2;
            speed = -speed;
        }
        std::cout << "Target Angle: " << target_angle << std::endl;
        std::cout << "Speed: " << speed << std::endl;
        std::cout << "Avg: " << avg << std::endl;
        std::cout << "Diff: " << diff << std::endl;
        
        this->spin(speed, -speed);
        diff -= (avg - prevAvg);
        prevAvg = avg;
        delay(20);
    }
    this->stop();
}

float Chassis::leftEncoder(rotationUnits units){
    return left->position(units);
}

float Chassis::rightEncoder(rotationUnits units){
    return right->position(units);
}


void Chassis::setBrakeType(brakeType type){
    left->setStopping(type);
    right->setStopping(type);
}

void Chassis::stop(){
    spin(0);
}