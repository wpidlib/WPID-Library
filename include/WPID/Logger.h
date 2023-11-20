#pragma once

#include <iostream>
#include "v5_vcs.h"

#define LOG_INFO(m) std::cout << "[INFO]" << vex::timer::system() << ":" << m << std::endl
#define LOG_WARN(m) std::cout << "[WARN]" << vex::timer::system() << ":" << m << std::endl
#define LOG_DEBUG(m) std::cout << "[DEBUG]" << vex::timer::system() << ":" << m << std::endl