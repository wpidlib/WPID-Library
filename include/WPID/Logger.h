#pragma once

#include <iostream>
#include "v5_vcs.h"

namespace wpid {
extern bool showDebug;
extern bool showWarn;
extern bool showInfo;

void LOG_WARN(std::string m);
void LOG_INFO(std::string m);
void LOG_DEBUG(std::string m);
}
