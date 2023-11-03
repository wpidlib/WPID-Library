#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "../PID.h"
#include <string>

using namespace vex;

class Mechanism {
private:
    //
    std::string name = "Mechanism";
    // Mechanism motors
    motor_group* motors;
    float gear_ratio; // the gear ration from motor to output
    PID pid; // the pid constants
    float offset = 0; // an offset to account for consistent error

    // Mechanism traits
    float max_acceleration = 0;
    float lower_bound = 0;
    float upper_bound = 0;
    int timeout = -9999;
    const float MAX_RAMP_DURATION = .25; // maximum duration based on target

    typedef struct _params {
        Mechanism* mech;
        float pos;
        float spd;
    } params;

    params* getParams(float position, float speed){
        params* p;
        p->mech = this;
        p->pos = position;
        p->spd = speed;
        return p;
    }
public:
    bool isSettled = true;
    /**
     * @brief Construct a new Mechanism object.
     * 
     * @param motors the motors used on the mechanism
     * @param gear_ratio the external gear ratio between motor group and mechanism
     */
    Mechanism(motor_group* motors, float gear_ratio);
    Mechanism() = default;

    /**
     * @brief Spins the motor group at the specified speed.
     * @param velocity the velocity of the lift
     */
    void spin(int velocity);

    /**
     * @brief stops the motors
     */
    void stop();

    void waitUntilSettled();

    /**
     * @brief Move the mechanism an absolute position asynchronously
     */
    void moveRelativeAsync(float position, float max_speed);

    /**
     * @brief Move the mechanism a relative position. Adds the position to the current state
     * 
     * 
     * @param position the position of the motor in the set rotationUnit
     * @param max_speed the maximum speed of the motors
     */
    void moveRelative(float position, float max_speed);

    /**
     * @brief Move the mechanism a relative position asynchronously
     */
    void moveAbsoluteAsync(float position, float max_speed);

    /**
     * @brief Move the mechanism to an absolute position
     * 
     * @param position the position of the motor in the set rotationUnit
     * @param max_speed the maximum speed of the motors
     */
    void moveAbsolute(float position, float max_speed);
    
    /**
     * @brief Move a mechanism using the parameters struct
     * 
     */
    static void moveMech(void* args);  

    /**
     * @brief Gets the position of the mechanism
     * 
     * @return float
     */
    float getPosition(rotationUnits units);

    /**
     * @brief resets the motor position
     * 
     */
    void resetPosition();

    /**
     * @brief Sets the brake type of the motors
     * @param brakeType the brake type (coast, brake or hold)
     */
    void setBrakeType(brakeType type);

    /**
     * @brief Set the PID constants and object to the mechanism
     * @param PID a PID object
     */
    void setPID(PID pid);

    /**
     * @brief Set the offset of the mechanism to add or subtract a constant angle
     * 
     * @param offset the offset
     */
    void setOffset(float offset);

    /**
     * @brief Set the max acceleration of the mechanism
     * 
     * @param max_accel an arbitrary value to increment to ramp the speed up
     */
    void setMaxAcceleration(float max_accel);

    /**
     * @brief Set the manual bounds of the mechanism, such that it is unable to spin past these points
     * 
     * @param lower_bound the lowest encoder value the mechanism may move to
     * @param upper_bound the highest encoder value the mechanism may move to
     */
    void setBounds(float lower_bound, float upper_bound);
    
    /**
     * @brief Set the timeout of the mechanism. Limits the time a `setPosition()` call takes. 
     * @param timeout the timeout in milliseconds
     */
    void setTimeout(int timeout);

    /**
     * @brief Set the name of the mechanism
     * 
     * @param name the name of the mechanism
     */
    void setName(char* name);
};
