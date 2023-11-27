#pragma once
#include "Tank.h"
#include <string>

namespace wpid {
class HDrive : public wpid::Tank {
    private:
        // Chassis scales specific for Tank Drive
        float center_wheel_circumference;
        // Left and Right motor groups for Tank
        Mechanism* center;
        // seperate PID objects for turning and straight motion
        PID pidStrafe;
        // offsets to fix steady state error
        float strafe_offset = 0;
        
        /**
         * @brief Sets the target position of each side of the chassis.
         * Uses the PID algorithm to determine speeds of the motors.
         * This function is inaccessable and is used as a helper.
         * @param left_target the left side's target in SOME UNITS
         * @param right_target the right side's target in SOME UNITS
         * @param center_target the center wheels' target in SOME UNITS
         * @param l_max_spd the max speed the left side should spin
         * @param r_max_spd the max speed the right side should spin
         * @param c_max_spd the max speed the center wheel should spin
         */
        void spinToTarget(float left_target, float right_target, float center_target, int l_max_spd, int r_max_spd, int c_max_spd);
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
         * @param drive_gear_ratio the internal gearset of the drive train
         */
        HDrive(float track_width, float wheel_radius, float center_wheel_radius, vex::motor_group* left, vex::motor_group* right, vex::motor_group* center, float drive_gear_ratio);
        HDrive() = default;

        /**
         * @brief Sets the straight line PID object.
         * @param pid a PID object holding the constants for driving straight 
         */
        void setStraightPID(PID pid) override;

        /**
         * @brief Sets the turning PID object.
         * @param pid a PID object holding the constants for turning on the spot
         */
        void setTurnPID(PID pid) override;

        /**
         * @brief Sets the strafing PID object.
         * @param pid a PID object holding the constants for strafing sideways
         */
        void setStrafePID(PID pid);
        
        /**
         * @brief Spin the entire chassis by specified velocities for each
         * side of the chassis. Negative values spin the wheel backwards.
         * @param left_velocity the left side velocity in percent units
         * @param right_velocity the right side velocity in percent units
         * @param center_velocity the center wheel velocity in percent units
         */
        void spin(int left_velocity, int right_velocity, int center_velocity);

        /**
         * @brief Spin the entire chassis by specified velocities for each
         * side of the chassis. Negative values spin the wheel backwards.
         * @param sides the side wheels' velocity in percent units
         * @param center the center wheel velocity in percent units
         */
        void spin(int sides, int center);

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
         * @brief Strafe the chassis sideways with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param distance the distance to travel in inches
         * @param max_speed the maximum speed in percent units
         */
        void strafe(float distance, int max_speed);

        /**
         * @brief Strafe the chassis sideways asyncrhonously with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param distance the distance to travel in inches
         * @param max_speed the maximum speed in percent units
         */
        void strafeAsync(float distance, int max_speed);

         /**
         * @brief Move the chassis on a diagonal a specific distance with PID.
         * Chassis will always stay at or below the maximum speed.
         * The speed of the center wheel is calculated in the function as being proportional to the distance traveled.
         * If the straight distance is 100, and center is 30, the center wheel will spin at 30% the speed of straight_max_speed.
         * @param straight_distance the distance going forward or backwards in inches
         * @param strafe_distance the distance going sideways in inches
         * @param straight_max_speed the maximum speed the robot will travel
         */
        void diagonal(float straight_distance, float strafe_distance, int straight_max_speed);

         /**
         * @brief Move the chassis on a diagonal asynchronously a specific distance with PID.
         * Chassis will always stay at or below the maximum speed.
         * The speed of the center wheel is calculated in the function as being proportional to the distance traveled.
         * If the straight distance is 100, and center is 30, the center wheel will spin at 30% the speed of straight_max_speed.
         * @param straight_distance the distance going forward or backwards in inches
         * @param strafe_distance the distance going sideways in inches
         * @param straight_max_speed the maximum speed the robot will travel
         */
        void diagonalAsync(float straight_distance, float strafe_distance, int straight_max_speed);

        /**
         * @brief Stops the chassis using the default brake mode.
         */
        void stop() override;

        /**
         * @brief Waits for the robot to finish a motion.
         */
        void waitUntilSettled() override;

         /**
         * @brief Gets the current position of the left side of the chassis.
         * 
         * @param unit the rotation units you want to return
         * @return the position in the specified units
         */
        float getLeftPosition(vex::rotationUnits units);

         /**
         * @brief Gets the current position of the right side of the chassis.
         * 
         * @param unit the rotation units you want to return
         * @return the position in the specified units
         */
        float getRightPosition(vex::rotationUnits units);

         /**
         * @brief Gets the current position of the center wheel of the chassis.
         * 
         * @param unit the rotation units you want to return
         * @return the position in the specified units
         */
        float getCenterPosition(vex::rotationUnits units);

        /**
         * @brief Reset all encoders to 0.
         */
        void resetPosition() override;

        /**
         * @brief Sets the brake type of the chassis.
         * @param type The brake type can be set to coast, brake, or hold.  
         */
        void setBrakeType(vex::brakeType type);

        /**
         * @brief Set the max acceleration of the mechanism. 
         * The value is arbitrary, between 0 and 1.
         * @param max_accel an arbitrary value to increment to ramp the speed up
         */
        void setMaxAcceleration(float max_accel);

        /**
         * @brief Set the offset for the straight and turn functions.
         * This value is in inches, and will add to the input of each movement funciton.
         * @param straight the distance to offset straight motion in inches
         * @param turn the angle to offset turns in degrees
         * @param strafe the distance to offset strafe motion in inches
         */
        void setOffset(float straight, float turn, float strafe);

        /**
         * @brief Set the measurement units for chassis values.
         * @param preferred_units the user's measurement system
         */
        void setMeasurementUnits(Conversion::measurement preferred_units);
};
}