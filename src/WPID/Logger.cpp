#include "WPID/Logger.h"

using namespace wpid;

bool showInfo = false;
bool showWarn = false;
bool showDebug = false;

void LOG(char* severity, char*m){
    std::cout << severity << vex::timer::system() << "ms:" << m << std::endl;
}
void LOG_DEBUG(char* m){
    if(wpid::showDebug)
        LOG("[DEBUG]", m);
}
void LOG_WARN(char* m){
    if(wpid::showWarn)
        LOG("[WARN]", m);
}
void LOG_INFO(char* m){
    if(wpid::showInfo)
        LOG("[INFO]", m);
}
