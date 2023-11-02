#pragma once
#include "Chassis.h"
#include <string>

namespace wpid{
class Tank : public Chassis{
    private:
        std::string name = "Tank Chassis";
        // Chassis scales specific for Tank Drive
        float track_width;
        float wheel_circumference;
        // Left and Right motor groups for Tank
        Mechanism* left;
        Mechanism* right;
        // seperate PID objects for turning and straight motion
        PID pidStraight;
        PID pidTurn;
        // offsets to fix steady state error
        float straight_offset = 0;
        float turn_offset = 0;
        // maximum acceleration for ramp
        float max_acceleration = .5;

        /**
         * @brief Sets the target position of each side of the chassis.
         * This uses an open loop algorithm to move the robot with PID to its target.
         * Does not use odometry to calculate error. Cannot adjust for sideways error.
         * @param left_target the left side's target in SOME UNITS
         * @param right_target the right side's target in SOME UNITS
         * @param l_max_spd the max speed the left side should spin
         * @param r_max_spd the max speed the right side should spin
         */
        void setTarget(float left_target, float right_target, int l_max_spd, int r_max_spd);

    public:
        /**
         * @brief Construct a new Chassis object. 
         * All distance units are assumed to be in inches.
         * 
         * @param track_width the width between left and right
         * @param wheel_base the distance from front to back of the wheel
         * @param wheel_radius radius of the wheel 
         * @param left motor group
         * @param right motor group
         */
        Tank(float track_width, float wheel_radius, motor_group* left, motor_group* right, float drive_gear_ratio);
        Tank() = default;

        /**
         * @brief Sets the straight line PID constants 
         * @param pid 
         */
        void setStraightPID(PID pid) override;

        /**
         * @brief Sets the turning PID constants
         * @param pid 
         */
        void setTurnPID(PID pid) override;

        /**
         * @brief Spin the entire chassis by specified velocities for each
         * side of the chassis. Negative values spin the weel backwards
         * 
         * @param left_velocity 
         * @param right_velocity 
         */
        void spin(int left_velocity, int right_velocity) override;

        /**
         * @brief Spin the entire chassis by specified velocities for both sides
         * @param velocity 
         */
        void spin(int velocity) override;

        /**
         * @brief Stops the chassis from moving
         */
        void stop() override;

        /**
         * @brief Move the chassis forward with the specified PID constants.
         * Chassis will always stay at or below the maximum speed.
         * @param distance 
         * @param max_speed 
         */
        void straight(float distance, int max_speed) override;

        /**
         * @brief Turn the chassis on the spot with the specified PID constants.
         * Chassis will always stay at or below the maximum speed.
         * @param target_angle 
         * @param max_speed 
         */
        void turn(int target_angle, int max_speed) override;

        /**
         * @brief Gets the current position of the left side of the chassis
         * 
         * @param units typically useing rotationUnits::deg
         * @return float 
         */
        float leftEncoder(rotationUnits units);

        /**
         * @brief Gets the current position of the right side of the chassis
         * 
         * @param units typically useing rotationUnits::deg
         * @return float 
         */
        float rightEncoder(rotationUnits units);

        /**
         * @brief Reset the left and right encoders to 0.
         */
        void resetEncoders() override;

        /**
         * @brief Sets the brake type of the chassis by passing a brake type as a parameter.
         * @param type The brake type can be set to coast, brake, or hold.  
         */
        void setBrakeType(brakeType type);

        /**
         * @brief Set the offset for straight and turn functions.
         * 
         * @param straight 
         * @param turn 
         */
        void setOffset(float straight, float turn);

        /**
        * @brief Set the max acceleration of the mechanism
        * 
        * @param max_accel an arbitrary value to increment to ramp the speed up
        */
        void setMaxAcceleration(float max_accel);

        /**
         * @brief Set the name of the chassis
         * 
         * @param name the name of the chassis
         */
        void setName(char* name);
};
}