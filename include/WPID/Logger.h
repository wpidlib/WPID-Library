#pragma once

#include <iostream>
#include <string>
#include "v5_vcs.h"

namespace wpid {
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
        operator << ("["+getLevel(type)+" ");
        operator << (vex::timer::system());
        operator << ("ms]");
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