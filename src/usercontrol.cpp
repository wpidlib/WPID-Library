#include "main.h"

// cubes value and returns as a proportion
double scale(double x) {
    return (x > 0 ? 100 : -100) * ((x/127) * (x/127)); 
}

int displayEncoders(){
    while(1){
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print("Left:  %d", chassis->leftEncoder(rotationUnits::rev));
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print("Right: %d", chassis->rightEncoder(rotationUnits::rev));
        this_thread::sleep_for(25);
    }
    return 0;
}

void usercontrol(){ 
    thread dispEnc = thread(displayEncoders);
    chassis->turn(90, 25);
    
    // chassis->forward(24, 40);
    // chassis->forward(6, 25);
    // chassis->forward(12, 30);
    // chassis->forward(-42, 50);
    
    // axis values on controller
    double axis3, axis4 = 0;
    while (1) {
        axis3 = scale(con->Axis3.value());
        axis4 = scale(con->Axis4.value());
        chassis->spin(axis3 + axis4, axis3 - axis4); 

        delay(20);
    }
}