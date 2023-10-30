#pragma once
#include "WPID/Chassis/Chassis.h"
#include "WPID/Chassis/Tank.h"

class HDrive: public Tank {
    private:
        // Chassis scales specific for Tank Drive
        float track_width;
        float wheel_circumference;
        float center_wheel_circumference;
        // Left and Right motor groups for Tank
        motor_group* left;
        motor_group* right;
        motor_group* center;
        // seperate PID objects for turning and straight motion
        PID pidStraight;
        PID pidTurn;
        PID pidStrafe;
        // external encoders to track left and right side
        encoder* leftEnc = nullptr;
        encoder* rightEnc = nullptr;
        encoder* centerEnc = nullptr;
        // offsets to fix steady state error
        float straight_offset = 0;
        float turn_offset = 0;
        float strafe_offset = 0;
        float max_acceleration = 0;
        /**
         * @brief Sets the target position of each side of the chassis.
         * This uses an open loop algorithm to move the robot with PID to its target.
         * Does not use odometry to calculate error. Cannot adjust for sideways error.
         * @param left_target the left side's target in SOME UNITS
         * @param right_target the right side's target in SOME UNITS
         * @param center_target the center wheels' target in SOME UNITES
         * @param l_max_spd the max speed the left side should spin
         * @param r_max_spd the max speed the right side should spin
         * @param c_max_spd the max speed the center wheel should spin
         * @param PID PID object to rely on
         */
        void setTarget(float left_target, float right_target, float center_target, int l_max_spd, int r_max_spd, int c_max_spd, PID pid);
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
         * @param center motor group
         */
        HDrive(float track_width, float wheel_radius, float center_wheel_radius, motor_group* left, motor_group* right, motor_group* center);
        HDrive() = default;

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
         * @brief Sets the strafe PID constants
         * @param pid 
         */
        void setStrafePID(PID pid);
        
        /**
         * @brief Spin the entire chassis by specified velocities for each
         * side of the chassis. Negative values spin the weel backwards
         * 
         * @param left_velocity 
         * @param right_velocity 
         * @param center_velocity
         */
        void spin(int left_velocity, int right_velocity, int center_velocity);

        /**
         * @brief 
         * 
         * @param velocity 
         */
        void spin(int sides, int center) override;

        /**
         * @brief Stops the chassis from moving
         */
        void stop() override;

        /**
         * @brief Reset the left and right encoders to 0.
         */
        void resetEncoders() override;

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
         * @brief Strage the chassis sideways a specified distance. 
         * 
         * @param distance sideways distance to travel
         * @param max_speed 
         */
        void strafe(float distance, int max_speed);

        /**
         * @brief Drives the robot on a diiagonal using the center and side wheels.
         * 
         * @param straight_distance forward and backwards distance
         * @param strafe_distance distance for the center wheel to travel
         * @param max_speed maximum speed for the robot
         */
        void diagonal(float straight_distance, float strafe_distance, int straight_max_speed);

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
         * @brief Gets the current position of the center wheel(s) of the chassis.
         * 
         * @param units 
         * @return float
         */
        float centerEncoder(rotationUnits units);

        /**
         * @brief Sets the encoders
         * 
         * @param left The left encoder
         * @param right The right encoder
         */
        void setEncoders(encoder* left, encoder* right, encoder* center);

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
        void setOffset(float straight, float turn, float strafe);

        void setMaxAcceleration(float max_accel){
            this->max_acceleration = max_accel;
        }
};