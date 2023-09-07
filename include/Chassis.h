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
        PID pidStraight;
        PID pidTurn;
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
        void spin(int left_velocity, int right_velocity);

        /**
         * @brief Spin the entire chassis by specified velocities for both sides
         * 
         * @param velocity 
         */
        void spin(int velocity);
        void stop();
        void forward(float distance, int max_velocity);
        void turn(float target_angle, int max_velocity);
        float leftEncoder(rotationUnits units);
        float rightEncoder(rotationUnits units);
        void setBrakeType(brakeType type);
};      
