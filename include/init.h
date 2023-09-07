#pragma once
#include "main.h"

using namespace vex;

extern brain Brain;
extern controller* con;

extern Chassis* chassis;

void init(void);
void delay(int msec);