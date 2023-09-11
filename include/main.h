#pragma once

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "v5.h"
#include "v5_vcs.h"
#include "Chassis.h"
#include "PID.h"
#include "init.h"

#define LOG(x) std::cout << x << std::endl

using namespace vex;

// Driver and Auton functions
void usercontrol();
void auton();