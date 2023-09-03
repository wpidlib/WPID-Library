#pragma once

class PID {
    private:
        float kp;
        float ki;
        float kd;
    public:
        PID() = default;
        PID(float kp, float ki, float kd);
        float PID::updateVelocity(float dist_from_target);
};      
