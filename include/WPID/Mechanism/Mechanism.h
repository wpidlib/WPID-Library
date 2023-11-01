#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "../PID.h"

using namespace vex;

class Mechanism {
private:
    motor_group* motors;
    float gear_ratio;
    PID pid;
    float offset = 0;

    float max_acceleration = 0;
    float upper_bound = MAXFLOAT;
    float lower_bound = -1;
public:
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

    /**
     * @brief Set the angle of the mechanism. The angle is the relative angle of your arm, in degrees.
     * 
     * 
     * @param angle 
     * @param max_speed 
     */
    void setAngle(float angle, float max_speed);

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

    void setMaxAcceleration(float max_accel);

    /**
     * @brief Set the manual bounds of the mechanism, such that it is unable to spin past these points
     * 
     * @param upper_bound the highest encoder value the mechanism may move to
     * @param lower_bound the lowest encoder value the mechanism may move to
     */
    void setBounds(float upper_bound, float lower_bound);
};
