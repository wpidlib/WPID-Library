#pragma once
#include "v5.h"
#include "PID.h"
using namespace vex;

class Chassis {
    private:
        float wheel_base;
        float wheel_radius;
        float wheel_circumference;
        motor_group* left;
        motor_group* right;
        PID pid;
    public:
        Chassis(float wheel_base, float wheel_radius, motor_group* left, motor_group* right);
        Chassis() = default;
        /**
         * @brief Spin the entire chassis by specified velocities for each
         * side of the chassis
         * 
         * @param left_velocity 
         * @param right_velocity 
         */
        void Chassis::spin(int left_velocity, int right_velocity);

        /**
         * @brief Spin the entire chassis by specified velocities for both sides
         * 
         * @param velocity 
         */
        void Chassis::spin(int velocity);
        
        void Chassis::forward(float distance, int max_velocity);
        void Chassis::turn(float target_angle, int max_velocity);
        float Chassis::getEncoderCount();
};      
