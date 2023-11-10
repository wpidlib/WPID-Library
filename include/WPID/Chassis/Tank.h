#pragma once
#include "Chassis.h"
#include <string>

namespace wpid{
class Tank : public wpid::Chassis{
    private:
        /**
         * @brief Sets the target position of each side of the chassis.
         * Uses the PID algorithm to determine speeds of the motors.
         * This function is inaccessable and is used as a helper.
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
         * @brief Sets the straight line PID object.
         * @param pid a PID object holding the constants for driving straight 
         */
        void setStraightPID(PID pid) override;

        /**
         * @brief Sets the turning PID constants.
         * @param pid a PID object holding the constants for turning on the spot
         */
        void setTurnPID(PID pid) override;

        /**
         * @brief Spin the entire chassis by specified velocities for each
         * side of the chassis. Negative values spin the wheel backwards.
         * @param left_velocity the left side velocity in percent units
         * @param right_velocity the right side velocity in percent units
         */
        void spin(int left_velocity, int right_velocity);

        /**
         * @brief Spin the entire chassis by specified velocities for both sides.
         * @param velocity the velocity in percent units
         */
        void spin(int velocity);

        /**
         * @brief Move the chassis forward a specific distance with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param distance the distance in inches
         * @param max_speed the maximum speed the robot will travel
         */
        void straight(float distance, int max_speed) override;

        /**
         * @brief Move the chassis forward asynchronously a specific distance with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param distance the distance in inches
         * @param max_speed the maximum speed the robot will travel
         */
        void straightAsync(float distance, int max_speed) override;

        /**
         * @brief Turn the chassis on the spot with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param target_angle the target angle in degrees
         * @param max_speed the maximum speed in percent units
         */
        void turn(int target_angle, int max_speed) override;

        /**
         * @brief Turn the chassis on the spot asynchronously with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param target_angle the target angle in degrees
         * @param max_speed the maximum speed in percent units
         */
        void turnAsync(float target_angle, int max_speed) override;

        /**
         * @brief Stops the chassis using the default brake mode.
         */
        void stop() override;

        /**
         * @brief Waits for the robot to finish a motion.
         */
        void waitUntilSettled() override;

        /**
         * @brief Gets the current position of the left side of the chassis
         * 
         * @param units typically using rotationUnits::deg
         * @return float 
         */
        float leftEncoder(rotationUnits units) override;

        /**
         * @brief Gets the current position of the right side of the chassis
         * 
         * @param units typically useing rotationUnits::deg
         * @return float 
         */
        float rightEncoder(rotationUnits units) override;

        /**
         * @brief Reset the left and right encoders to 0.
         */
        void resetEncoders() override;

        /**
         * @brief Sets the brake type of the chassis by passing a brake type as a parameter.
         * @param type The brake type can be set to coast, brake, or hold.  
         */
        void setBrakeType(brakeType type) override;

        /**
         * @brief Set the max acceleration of the mechanism. 
         * The value is arbitrary, between 0 and 1.
         * @param max_accel an arbitrary value to increment to ramp the speed up
         */
        void setMaxAcceleration(float max_accel) override;

        /**
         * @brief Set the offset for the straight and turn functions.
         * This value is in inches, and will add to the input of each movement funciton.
         * @param straight the distance to offset straight motion in inches
         * @param turn the angle to offset turns in degrees
         */
        void setOffset(float straight, float turn);

};
}