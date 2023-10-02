#pragma once
#include "main.h"

extern brain Brain;
extern controller* con;

extern Chassis* chassis;


extern triport tport;
extern encoder lenc;
extern encoder renc;

void init(void);
void delay(int msec);