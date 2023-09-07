#include "main.h"
#include <algorithm>

PID::PID(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd) {}

float PID::updateVelocity(float dist_from_target, float max_velocity){
    float speed = max_velocity * (kp * dist_from_target);
    return dist_from_target > 0 ? std::min(max_velocity, speed) : std::max(max_velocity*-1, speed);
}
