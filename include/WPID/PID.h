#pragma once
#include "v5_vcs.h"
#include "stdint.h"
#include <sstream>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <fstream>
#include "./Logger.h"

class PID {
    private:
        float kp; // proportional constant
        float ki; // integral constant
        float kd; // derivative constant
        float bound = 1; //the error bound
        float prev_error = MAXFLOAT; // the previous error
        float prev_integral = 0; // the previous integral
        std::string fName = "LoggedData";
    public:
        int delay_time = 20; // delay in milliseconds
        int bias = 0; // lowest speed possible for PID to achieve
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
         * @brief Used to update the velocity of a motor or motor group. The speed
         * is proportional to the distance remaining from the target.
         * 
         * @param error the remaining distance to the target, any unit is allowed
         * @param max_speed maximum velocity allowed, any unit is allowed
         * @param mech_id string identifier for motor group to log
         * @return a calculated speed based on all parameters
         */
        float calculateSpeed(float error, float max_speed, std::string mech_id);

        /**
         * @brief Set the error range.
         * @param bound the absolute value of the bound of the error range
         */
        void setErrorRange(float bound);

        /**
         * @brief Checks if the current error is within the error range.
         * @param error the current error of the system
         * @return true if the error is outside the bounds, false if it is within the bounds
         */
        bool unfinished(float error);

        /**
         * @brief Reset the previous error and previous integral values.
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
         * @param error is the robot error value
         * @param speed is the robots speed
         * @param proportional is the P value for PID
         * @param integral is the I value for PID
         * @param derivative is the D value for PID
         * @param motor_id is the motor identifier for graphing
         */
        void fileLogging(float error, float speed, float proportional, float integral, float derivative, std::string mech_id);
};      
