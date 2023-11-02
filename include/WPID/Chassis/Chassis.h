#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "../PID.h"
#include "../Mechanism/Mechanism.h"

using namespace vex;

class Chassis {
    public:
        /**
         * @brief Sets the straight line PID constants 
         * @param pid 
         */
        virtual void setStraightPID(PID pid) = 0;

        /**
         * @brief Sets the turning PID constants
         * @param pid 
         */
        virtual void setTurnPID(PID pid) = 0;

        /**
         * @brief Spin the entire chassis by specified velocities for each
         * side of the chassis. Negative values spin the weel backwards
         * 
         * @param left_velocity 
         * @param right_velocity 
         */
        virtual void spin(int left_velocity, int right_velocity) = 0;

        /**
         * @brief Spin the entire chassis by specified velocities for both sides
         * @param velocity 
         */
        virtual void spin(int velocity) = 0;

        /**
         * @brief Stops the chassis from moving
         */
        virtual void stop() = 0;

        /**
         * @brief Reset the left and right encoders to 0.
         */
        virtual void resetEncoders() = 0;

        /**
         * @brief Move the chassis forward with the specified PID constants.
         * Chassis will always stay at or below the maximum speed.
         * @param distance 
         * @param max_speed 
         */
        virtual void straight(float distance, int max_speed) = 0;

        /**
         * @brief Turn the chassis on the spot with the specified PID constants.
         * Chassis will always stay at or below the maximum speed.
         * @param target_angle 
         * @param max_speed 
         */
        virtual void turn(int target_angle, int max_speed) = 0;
        /**
         * @brief Sets the target position of each side of the chassis.
         * This uses an open loop algorithm to move the robot with PID to its target.
         * Does not use odometry to calculate error. Cannot adjust for sideways error.
         * @param left_target the left side's target in SOME UNITS
         * @param right_target the right side's target in SOME UNITS
         * @param l_max_spd the max speed the left side should spin
         * @param r_max_spd the max speed the right side should spin
         * @param PID PID object to rely on
         */
        virtual void setTarget(float left_target, float right_target, int l_max_spd, int r_max_spd) = 0;
};