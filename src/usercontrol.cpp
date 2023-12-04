#include "main.h"
#include <iostream>
#include <thread>

// cubes value and returns as a proportion
double scale(double x) {
    return (x > 0 ? 100 : -100) * ((x/127) * (x/127)); 
}

int printInDriverControl(){
    while(1){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(30, 30);
        Brain.Screen.print("In DRIVER CONTROL mode");
        this_thread::sleep_for(25);
    }
    return 0;
}

void usercontrol(){ 
    auton();
    thread printAngleThread = thread(printInDriverControl);
    //Brain.Screen.printAt(1, 1, "IN DRIVER CONTROL");
    // axis values on controller
    double axis1, axis3, axis4= 0;
    while (1) {
        axis3 = scale(con->Axis3.value());
        axis4 = scale(con->Axis4.value());
        axis1 = scale(con->Axis1.value());
    

        // if(con->ButtonR1.pressing()){
        //     fourbar->spin(20);
        // } else if (con->ButtonR2.pressing()) {
        //     fourbar->spin(-20);
        // } else {
        //     fourbar->stop();
        // }

        if(con->ButtonDown.pressing()){
            chassis->spin(-20,0);
        } else {
            chassis->spin(axis3 + axis4, axis3 - axis4, axis1);
        }
        
        wait(20, msec);
    }
}