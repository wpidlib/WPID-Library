#pragma once

class PID {
    private:
        float kp;
        float ki;
        float kd;
    public:
        PID() = default;
        PID(float kp, float ki, float kd);
        float updateVelocity(float dist_from_target, float max_velocity);
};      
