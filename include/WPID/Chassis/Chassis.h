#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "../PID.h"
#include "../Mechanism/Mechanism.h"
#include "../Logger.h"
#include "../Conversion.h"

namespace wpid {
/**
 * @brief A pure virtual class to define the behavior and attributes 
 * of a chassis. Classes that extend this class will defualt to the 
 * behavior defined here, which for all methods is to do nothing.
 */
class Chassis {
    protected:
        /** 
        * Chassis track width for Tank drive
        */
        float track_width;
        
        /**
         * Chassis wheel circumference
         */
        float wheel_circumference;

        /** 
        * Left and Right mechanisms
        */
        Mechanism* left;
        Mechanism* right;

        /** 
        * PID objects for straight and turning motion
        */
        PID pidStraight;
        PID pidTurn;

        /**
        * Offsets to fix consistent error
        */
        float straight_offset = 0;
        float turn_offset = 0;
        
        /**
        * Maximum acceleration for ramp
        */
        float max_acceleration = 1;
        
        /**
        * The units used for distances
        */
        Conversion::measurement measure_units = Conversion::measurement::in;
    public:
        /**
         * @brief Sets the straight PID object.
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
        virtual float getLeftPosition(vex::rotationUnits units) = 0;
        
         /**
         * @brief Gets the current position of the right side of the chassis.
         * 
         * @param unit the rotation units you want to return
         * @return the position in the specified units
         */
        virtual float getRightPosition(vex::rotationUnits units) = 0;
        
        /**
         * @brief Reset all encoders to 0.
         */
        virtual void resetPosition() = 0;

        /**
         * @brief Sets the brake type of the chassis.
         * @param type The brake type can be set to coast, brake, or hold.  
         */
        virtual void setBrakeType(vex::brakeType type) = 0;

        /**
         * @brief Set the max acceleration of the chassis. 
         * The value is arbitrary, between 0 and 1.
         * @param max_accel an arbitrary value to increment to ramp the speed up
         */
        virtual void setMaxAcceleration(float max_accel) = 0;

        /**
         * @brief Set the measurement units for chassis values.
         * @param preferred_units the user's measurement system
         */
        virtual void setMeasurementUnits(Conversion::measurement preferred_units) = 0;
};
}