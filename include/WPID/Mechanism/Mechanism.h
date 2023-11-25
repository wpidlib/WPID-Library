#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "../Logger.h"
#include "../PID.h"
#include <string>

namespace wpid{
class Mechanism {
private:
    //
    std::string name = "Mechanism";
    // Mechanism motors
    vex::motor_group* motors;
    float gear_ratio; // the gear ration from motor to output
    PID pid; // the pid constants
    float offset = 0; // an offset to account for consistent error
    std::string mech_id; // the string identifier for the motor group for logging purposes

    // Mechanism traits
    float max_acceleration = 0;
    float upper_bound = MAXFLOAT; // the upper bound to limit motion
    float lower_bound = -MAXFLOAT; // the lower bound to limit motion
    const float MAX_RAMP_DURATION = .25; // maximum duration based on target

    // A struct to store position, speed and the pointer to this mechanism
    typedef struct params {
        Mechanism* mech;
        float pos;
        float spd;
    }params;

    /**
     * @brief Get an instance of a param struct pointer to pass to setTarget.
     * Used as a helper funciton to pass multple parameters into a thread.
     * @param position the position target
     * @param speed the max speed
     * @return params* a parameter pointer
     */
    params* getParams(float position, float speed){
        params* p = new params;
        p->mech = this;
        p->pos = position;
        p->spd = speed;
        return p;
    }

    /**
     * @brief Sets the target position of the mechanism.
     * Uses the PID algorithm to determine speeds of the motors.
     * This function is inaccessable and is used as a helper.
     * @param args the parameter arguments to set the target
     */
    static void spinToTarget(void* args);  
public:
    bool isSettled = true;
    /**
     * @brief Construct a new Mechanism object.
     * 
     * @param motors the motors used on the mechanism
     * @param gear_ratio the external gear ratio between motor group and mechanism
     * @param motor_id the string identifier for the motor group to enable per motor logging
     */
    Mechanism(vex::motor_group* motors, float gear_ratio, std::string mech_id);
    Mechanism(vex::motor_group* motors, float gear_ratio);
    Mechanism() = default;

    /**
     * @brief Spins the motor group at the specified velocity.
     * Negative values will spin the motors backwards.
     * @param velocity the velocity of the mechanism
     */
    void spin(int velocity);

    /**
     * @brief stops the motors using the default brake mode.
     */
    void stop();

    /**
     * @brief Waits for the mechanism to finish motion.
     */
    void waitUntilSettled();

    /**
     * @brief Move the mechanism to a relative angle.
     * 
     * @param position the relative angle to move to in degrees
     * @param max_speed the max speed of the motors
     */
    void moveRelative(float position, float max_speed);

    /**
     * @brief Move the mechanism to a relative angle asynchronously
     * 
     * @param position the relative angle to move to in degrees
     * @param max_speed the max speed of the motors
     */
    void moveRelativeAsync(float position, float max_speed);

    /**
     * @brief Move the mechanism to an absolute angle.
     * 
     * @param position the absolute angle to move to in degrees
     * @param max_speed the max speed of the motors
     */
    void moveAbsolute(float position, float max_speed);

    /**
     * @brief Move the mechanism to an absolute angle asynchronously
     * 
     * @param position the absolute angle to move to in degrees
     * @param max_speed the max speed of the motors
     */
    void moveAbsoluteAsync(float position, float max_speed);
    
    /**
     * @brief Get the position of the first motor in the group in the specified units.
     * 
     * @param units the rotation units to return
     * @return float the position of the motor
     */
    float getPosition(vex::rotationUnits units);

    /**
     * @brief Resets the encoders in the group to 0.
     */
    void resetPosition();

    /**
     * @brief Sets the brake type of the chassis.
     * @param type The brake type can be set to coast, brake, or hold.  
     */
    void setBrakeType(vex::brakeType type);

    /**
     * @brief Set a PID object to the mechanism
     * @param PID a PID object
     */
    void setPID(PID pid);

    /**
     * @brief Set the offset of the mechanism to add or subtract a constant angle
     * 
     * @param offset the offset in degrees
     */
    void setOffset(float offset);

    /**
     * @brief Set the max acceleration of the mechanism. 
     * The value is arbitrary, between 0 and 1.
     * @param max_accel an arbitrary value to increment to ramp the speed up
     */
    void setMaxAcceleration(float max_accel);

    /**
     * @brief Set the manual bounds of the mechanism, such that it is unable to spin past these points.
     * 
     * @param lower_bound the lowest encoder value the mechanism may move to
     * @param upper_bound the highest encoder value the mechanism may move to
     */
    void setBounds(float lower_bound, float upper_bound);
};
}