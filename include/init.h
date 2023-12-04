#pragma once
#include <cmath>
#include <string.h>
#include "v5_vcs.h"
#include "WPID/wpid.h"

using namespace wpid;
using namespace vex;

extern brain Brain;
extern controller* con;

extern HDrive* chassis;
extern Mechanism* fourbar;

void init(void);