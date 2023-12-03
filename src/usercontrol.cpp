#include "main.h"
#include <iostream>
#include <thread>

// cubes value and returns as a proportion
double scale(double x) {
    return (x > 0 ? 100 : -100) * ((x/127) * (x/127)); 
}

void usercontrol(){ 
    auton();
    // axis values on controller
    double axis3, axis4 = 0;
    while (1) {
        axis3 = scale(con->Axis3.value());
        axis4 = scale(con->Axis4.value());

        if(con->ButtonR1.pressing()){
            fourbar->spin(20);
        } else if (con->ButtonR2.pressing()) {
            fourbar->spin(-20);
        } else {
            fourbar->stop();
        }

        if(con->ButtonDown.pressing()){
            chassis->spin(-20);
        } else {
            chassis->spin(axis3 + axis4, axis3 - axis4);
        }
        
        wait(20, msec);
    }
}