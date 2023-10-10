#pragma once
#include <cmath>
#include <string.h>
#include "v5_vcs.h"
#include "WPID/Tank.h"

using namespace vex;

extern brain Brain;
extern controller* con;

extern Tank* chassis;

extern triport tport;
extern encoder lenc;
extern encoder renc;

void init(void);
void delay(int msec);