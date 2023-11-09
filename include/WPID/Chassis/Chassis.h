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
         * @brief Sets the straight line PID object 
         * @param pid a PID object holding the correct constants for straight driving
         */
        virtual void setStraightPID(PID pid) = 0;

        /**
         * @brief Sets the turning PID constants
         * @param pid a PID onject holding the correct constants for turning on the spot
         */
        virtual void setTurnPID(PID pid) = 0;
        
        /**
         * @brief Stops the chassis using the default brake mode.
         */
        virtual void stop() = 0;

         /**
         * @brief Gets the current position of the left side of the chassis
         * 
         * @param units typically using rotationUnits::deg
         * @return float 
         */
        virtual float leftEncoder(rotationUnits units) = 0;
        
        /**
         * @brief Gets the current position of the right side of the chassis
         * 
         * @param units typically useing rotationUnits::deg
         * @return float 
         */
        virtual float rightEncoder(rotationUnits units) = 0;
        
        /**
         * @brief Reset all encoders to 0.
         */
        virtual void resetEncoders() = 0;

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
         * @brief Turn the chassis on the spot with the specified PID constants.
         * Chassis will always stay at or below the maximum speed.
         * @param target_angle 
         * @param max_speed 
         */
        virtual void turn(int target_angle, int max_speed) = 0;

        /**
         * @brief 
         * 
         * @param target_angle 
         * @param max_speed 
         */
        virtual void turnAsync(float target_angle, int max_speed) = 0;

        /**
         * @brief 
         * 
         */
        virtual void waitUntilSettled() = 0;

        /**
         * @brief Sets the brake type of the chassis by passing a brake type as a parameter.
         * @param type The brake type can be set to coast, brake, or hold.  
         */
        virtual void setBrakeType(brakeType type) = 0;

        /**
         * @brief Set the max acceleration of the mechanism
         * 
         * @param max_accel an arbitrary value to increment to ramp the speed up
         */
        virtual void setMaxAcceleration(float max_accel) = 0;
};
}