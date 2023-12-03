#pragma once
#include "v5_vcs.h"
#include "stdint.h"
#include <sstream>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <fstream>
#include "./Logger.h"

namespace wpid{
class PID {
    private:
        // PID constants
        /**
        * Proportional Constant
        */
        float kp;

        /**
        * Integral Constant
        */
        float ki;

        /**
        * Derivative Constant
        */
        float kd;

        // Stored values
        /**
        * The Previous Error
        */
        float prev_error = MAXFLOAT;

        /**
        * The Previous Integral
        */
        float prev_integral = 0;

        /*
        * The previous estimate for the derivative term 
        */
        float previous_estimate = 0;

        /*
        * The starting time for a PID run
        */
        int start_time = -1;

        // Tuneable attributes
        /**
        * The error bound in rotationUnits::deg
        */
        float bound = 1;

        /**
        * PID loop delay in milliseconds
        */
        int delay_time = 20;

        /**
        * Lowest speed possible for the PID to achieve
        */
        int bias = 0; 

        /**
         * A threshold to check for when the system is slow enough to stop
         */
        int low_speed_threshold = 2;

        /**
         * The timeout in milliseconds for how long a movement should take. 
         * Will stop the movement regardless of error when timeout is exceeded.
         */
        int timeout = -1;

        /**
         * The maximum output of the integral term. Unit is velocityUnits::pct
         */
        int max_integral_speed = 10;

        /**
        * Base name of the logging file
        */
        std::string fName = "LoggedData";
        
    public:       
        /**
         * @brief Construct a new PID object.
         * When constructing a PID object, only the kp constant is required, 
         * ki and kd can be set to 0 if not used.
         * @param kp proportional constant
         * @param ki integral constant
         * @param kd derrivative constant
         */
        PID(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd){};
        PID() = default;

        /**
         * @brief Used to calculate the velocity of a motor or motor group. 
         * The speed is calculated using PID, with integral clamping, bias maintaining, and speed clamping. 
         * 
         * @param error the remaining distance to the target
         * @param max_speed maximum velocity allowed in velocityUnits::pct
         * @param mech_id string identifier for motor group to log
         * @return a calculated speed based on all PID parameters
         */
        float calculateSpeed(float error, float max_speed, std::string mech_id);

        /**
         * @brief Set the error range in rotationUnits::deg.
         * @param bound the absolute value of the bounds of the error range
         */
        void setErrorRange(float bound);

        /**
         * @brief Set the delay used in the PID loop.
         * Default value is 20ms.
         * @param delay in milliseconds
         */
        void setDelayTime(int delay);

        /**
         * @brief Gets the delay time of this PID object in milliseconds.
         * 
         * @return int milliseconds
         */
        int getDelayTime();

        /**
         * @brief Set the bias, or the lowest speed possible for the system.
         * Default value is 0.
         * @param bias in velocityUnits::pct
         */
        void setBias(int bias);

        /**
         * @brief Set the low speed threshold to determine when the system is slow.
         * If the speed of the system is below this threshold, the loop will end if 
         * it is also within the error range. Otherwise the system will continue to 
         * correct for any error
         * 
         * @param threshold in velocityUnits::pct
         */
        void setLowSpeedThreshold(int threshold);

        /**
         * @brief Set the timeout to use for PID movement. If the timeout is exceeded, 
         * the system will stop regardless of the current error or speed.
         * A value of -1 will disable timeouts.
         * @param timeout in milliseconds
         */
        void setTimeout(int timeout);

        /**
         * @brief Set the maximum value the integral term will contribute to the speed calculations. 
         * If the integral term exceeds this value, it will be reduced to this value.
         * 
         * @param max_integral in velocityUnits::pct
         */
        void setMaxIntegral(int max_integral);

        /**
         * @brief Checks if the movement is unfinished (error still outside the final bounds).
         * @param error the current error of the system
         * @return returns true if the error is outside the bounds, false if it is within the bounds
         */
        bool unfinished(float error, int speed);

        /**
         * @brief Resets the previous error and previous integral values.
         */
        void reset(void);

        /**
         * @brief Duplicates the PID object by copying constants and returning a new PID object.
         * Used as a helper for using the same constants on multiple mechanisms.
         * @return PID 
         */
        PID copy(void);

        /**
         * @brief Logs the error, speed, integral and derivative values 
         * to a text file on a micro SD card on the robot
         * @param error the robot error value
         * @param speed the calculated speed
         * @param proportional result of the proportional calculation
         * @param integral result of the integral calculation
         * @param derivative result of the derivative calculation
         * @param mech_id the mechanism name
         */
        void fileLogging(float error, float speed, float proportional, float integral, float derivative, std::string mech_id);
};      
}