#include "main.h"

PID::PID(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd) {}

float PID::updateVelocity(float dist_from_target){
    return kp * dist_from_target;
}