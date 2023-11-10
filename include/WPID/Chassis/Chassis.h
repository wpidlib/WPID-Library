#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "../PID.h"
#include "../Mechanism/Mechanism.h"

using namespace vex;

namespace wpid {
class Chassis {
    protected:
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
    public:
        /**
         * @brief Sets the straight line PID object.
         * @param pid a PID object holding the constants for driving straight
         */
        virtual void setStraightPID(PID pid) = 0;

        /**
         * @brief Sets the turning PID object.
         * @param pid a PID onject holding the constants for turning on the spot
         */
        virtual void setTurnPID(PID pid) = 0;

        /**
         * @brief Move the chassis forward a specific distance with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param distance the distance in inches
         * @param max_speed the maximum speed the robot will travel
         */
        virtual void straight(float distance, int max_speed) = 0;

        /**
         * @brief Move the chassis forward asynchronously a specific distance with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param distance the distance in inches
         * @param max_speed the maximum speed the robot will travel
         */
        virtual void straightAsync(float distance, int max_speed) = 0;

        /**
         * @brief Turn the chassis on the spot with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param target_angle the target angle in degrees
         * @param max_speed the maximum speed in percent units
         */
        virtual void turn(int target_angle, int max_speed) = 0;

        /**
         * @brief Turn the chassis on the spot asynchronously with PID.
         * Chassis will always stay at or below the maximum speed.
         * @param target_angle the target angle in degrees
         * @param max_speed the maximum speed in percent units
         */
        virtual void turnAsync(float target_angle, int max_speed) = 0;

        /**
         * @brief Stops the chassis using the default brake mode.
         */
        virtual void stop() = 0;

        /**
         * @brief Waits for the robot to finish a motion.
         */
        virtual void waitUntilSettled() = 0;

         /**
         * @brief Gets the current position of the left side of the chassis.
         * 
         * @param unit the rotation units you want to return
         * @return the position in the specified units
         */
        virtual float leftEncoder(rotationUnits units) = 0;
        
         /**
         * @brief Gets the current position of the right side of the chassis.
         * 
         * @param unit the rotation units you want to return
         * @return the position in the specified units
         */
        virtual float rightEncoder(rotationUnits units) = 0;
        
        /**
         * @brief Reset all encoders to 0.
         */
        virtual void resetEncoders() = 0;

        /**
         * @brief Sets the brake type of the chassis.
         * @param type The brake type can be set to coast, brake, or hold.  
         */
        virtual void setBrakeType(brakeType type) = 0;

        /**
         * @brief Set the max acceleration of the chassis. 
         * The value is arbitrary, between 0 and 1.
         * @param max_accel an arbitrary value to increment to ramp the speed up
         */
        virtual void setMaxAcceleration(float max_accel) = 0;
};
}