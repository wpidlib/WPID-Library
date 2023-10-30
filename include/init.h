#pragma once
#include <cmath>
#include <string.h>
#include "v5_vcs.h"
#include "WPID/Chassis/HDrive.h"
#include "WPID/Mechanism/Mechanism.h"

using namespace vex;

extern brain Brain;
extern controller* con;

extern Tank* chassis;
extern Mechanism* fourbar;

// extern triport tport;
// extern encoder lenc;
// extern encoder renc;

void init(void);