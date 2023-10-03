#pragma once

class PID {
    private:
        float kp;
        float ki;
        float kd;
        float bound = 1; //default in case setErrorRange() is not called in init
        float prev_error = MAXFLOAT;
        float prev_integral = 0;
        std::string fName = "LoggedData";
    public:
        int delay_time = 20; // delay in milliseconds
        int bias = 0; // lowest speed possible for PID to achieve
        /**
         * @brief Construct a new PID object
         * When constructing a PID object, only the kp constant is required, 
         * ki and kd can be set to 0 if not used
         * @param kp proportional constant
         * @param ki integral constant
         * @param kd derrivative constant
         */
        PID(float kp, float ki, float kd);
        PID() = default;

        /**
         * @brief Used to update the velocity of a motor or motor group. The speed
         * is proportional to the distance remaining from the target. KP is used
         * 
         * @param error any unit is allowed, change constant parameters to adjust the behavior
         * @param max_speed maximum velocity allowed, any unit is allowed
         * @return float 
         */
        float calculateSpeed(float error, float max_speed);

        /**
         * @brief Set the error range
         * @param bound the absolute value of the bound of the error range
         */
        void setErrorRange(float bound);

        /**
         * @brief check if the current error is within the error range
         * @param error true if continue, false if stop
         * @return boolean
         */
        bool cont(float error);

        /**
         * @brief Reset the previous error and previous integral values.
         */
        void reset(void);

        /**
         * @brief Logs the error, speed, integral and derivative values 
         * to a text file on a micro SD card on the robot
         * @param error is the robot error value
         * @param speed is the robots speed
         * @param proportional is the P value for PID
         * @param integral is the I value for PID
         * @param derivative is the D value for PID
         */
        void logCSV(float error, float speed, float proportional, float integral, float derivative);

        PID copy();
};      
