#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "../Logger.h"
#include "../PID.h"
#include <string>

namespace wpid{
/**
 * @brief A Mechanism class that uses PID to control a motor group. 
 * Contains functions for moving to a relative or absolute angle both synchronously and asynchronously.
 */
class Mechanism {
private:
    /**
    * Mechanism Name
    */
    std::string name = "Mechanism";

    /**
    * Mechanism motors
    */
    vex::motor_group* motors;

    /**
    * The Gear ratio from motor to output
    */
    float gear_ratio;

    /**
    * The PID Constants
    */
    PID pid;
    
    /**
    * An offset to account for consistent error
    */
    float offset = 0;

    /**
    * The string identifier for the motor group for logging purposes
    */
    std::string mech_id;

    /**
    * The Max acceleration of the mechanism
    */
    float max_acceleration = 0;

    /**
    * The upper bound to limit mechanism motion
    */
    float upper_bound = MAXFLOAT;
    /**
    * The lower bound to limit mechanism motion
    */
    float lower_bound = -MAXFLOAT;

    /**
    * A struct to store position, speed and the pointer to this mechanism
    */
    typedef struct params {
        Mechanism* mech;
        float pos;
        float spd;
    }params;

    /**
     * @brief Get an instance of a param struct pointer to pass to setTarget.
     * Used as a helper function to pass multiple parameters into a thread.
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
     * This function is inaccessible and is used as a helper.
     * @param args the parameter arguments to set the target
     */
    static void spinToTarget(void* args);  

    /**
     * @brief The main thread responsible for spinning the motors 
     * and calculating speeds using PID.
     */
    vex::thread* mech_thread;
    
public:
    /**
     * @brief Construct a new Mechanism object.
     * 
     * @param motors the motors used on the mechanism
     * @param gear_ratio the external gear ratio
     * @param mech_id a string identifier for the mechanism to use during logging
     */
    Mechanism(vex::motor_group motors, float gear_ratio, std::string mech_id);
    Mechanism(vex::motor_group motors, float gear_ratio);
    Mechanism() = default;

    /**
     * @brief Spins the motor group at the specified velocity.
     * Negative values will spin the motors backwards.
     * @param velocity the velocity of the mechanism in velocityUnits::pct
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
     * @param max_speed the max speed of the motors in velocityUnits::pct
     */
    void moveRelative(float position, float max_speed);

    /**
     * @brief Move the mechanism to a relative angle asynchronously
     * 
     * @param position the relative angle to move to in degrees
     * @param max_speed the max speed of the motors in velocityUnits::pct
     */
    void moveRelativeAsync(float position, float max_speed);

    /**
     * @brief Move the mechanism to an absolute angle.
     * 
     * @param position the absolute angle to move to in degrees
     * @param max_speed the max speed of the motors in velocityUnits::pct
     */
    void moveAbsolute(float position, float max_speed);

    /**
     * @brief Move the mechanism to an absolute angle asynchronously
     * 
     * @param position the absolute angle to move to in degrees
     * @param max_speed the max speed of the motors in velocityUnits::pct
     */
    void moveAbsoluteAsync(float position, float max_speed);
    
    /**
     * @brief Get the position of the first motor in the group with the specified units.
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
     * @param type The brake type can be set to coast, brake, or hold
     */
    void setBrakeType(vex::brakeType type);

    /**
     * @brief Set a PID object to the mechanism.
     * @param PID a PID object
     */
    void setPID(PID pid);

    /**
     * @brief Set the offset of the mechanism to add or subtract a constant angle.
     * 
     * @param offset the offset in degrees
     */
    void setOffset(float offset);

    /**
     * @brief Set the max acceleration of the mechanism. 
     * Every time the PID loop executes, it increments the speed of the 
     * mechanism by this value until the mechanism reaches it's maximum speed. 
     * Increase the value if the robot is ramping too slow, or decrease if it causes too much jerk.
     * @param max_accel a value to increment to ramp the speed up in velocityUnits::pct
     */
    void setMaxAcceleration(float max_accel);

    /**
     * @brief Set the bounds of the mechanism, such that it is unable to spin past these points.
     * This check is only done during driver control and does not affect PID motion. 
     * @param lower_bound the lowest encoder value the mechanism may move to in degrees
     * @param upper_bound the highest encoder value the mechanism may move to in degrees
     */
    void setBounds(float lower_bound, float upper_bound);
};
}