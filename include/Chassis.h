#pragma once
#include "v5.h"
#include "PID.h"
using namespace vex;

class Chassis {
    private:
        float wheel_base;
        float wheel_radius;
        float wheel_circumference;
        int num_motors;
        motor** left;
        motor** right;
        PID pid;
    public:
        Chassis(float wheel_base, float wheel_radius, int motorL[], int motorR[]);
        Chassis() = default;
        void Chassis::forward(float distance, float max_velocity);
        void Chassis::turn(float target_angle, float max_velocity);
        float Chassis::getEncoderCount();
        void Chassis::setSideVelocity(float velocity, char side);
};      
