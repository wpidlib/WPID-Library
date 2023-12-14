/**
 * This logger was adapted from an example on Stack Overflow.
 * https://stackoverflow.com/questions/5028302/small-logger-class
 */
#pragma once

#include <iostream>
#include <string>
#include "v5_vcs.h"

namespace wpid {
/**
 * @brief A simple logger class that can be used to log messages to the console.
 * Contains 3 different logging levels, DEBUG, INFO, and WARN. 
 */
enum logType {
    DEBUG,
    INFO,
    WARN
};

class LOG{
public:
    LOG(){}
    LOG(logType type){
        msg_level = type;
        operator << ("[");
        operator << (vex::timer::system());
        operator << ("]");
        operator << ("["+getLevel(type)+"]");
    }
    ~LOG(){
        if(opened){
            std::cout << std::endl;
        }
        opened = false;
    }
    template<class T>
    LOG &operator<<(const T &msg){
        if(msg_level >= base_level){
            std::cout << msg;
            opened = true;
        }
        return *this;
    }
    void setBaseLevel(logType type) {base_level = type;}
private:
    inline static logType base_level = DEBUG;
    bool opened = false;
    logType msg_level = DEBUG;
    inline std::string getLevel(logType type){
        std::string label;
        switch (type) {
            case DEBUG: label = "DEBUG"; break;
            case WARN:  label = "WARN" ; break;
            case INFO:  label = "INFO" ; break;
        }
        return label;
    }
};
}