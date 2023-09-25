#include "main.h"

// cubes value and returns as a proportion
double scale(double x) {
    return (x > 0 ? 100 : -100) * ((x/127) * (x/127)); 
}

int displayEncoders(){
    while(1){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print("Left:  %f", chassis->leftEncoder(rotationUnits::deg));
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print("Right: %f", chassis->rightEncoder(rotationUnits::deg));
        this_thread::sleep_for(25);
    }
    return 0;
}

void usercontrol(){ 
    thread dispEnc = thread(displayEncoders);   
    for(int i = 0; i < 4; i++){
        chassis->engage(1, 1);
        chassis->forward(24, 40); 
        chassis->engage(-1, 1);
        chassis->turn(90, 25);
    }
        
    
    
    // axis values on controller
    double axis3, axis4 = 0;
    while (1) {
        axis3 = scale(con->Axis3.value());
        axis4 = scale(con->Axis4.value());
        chassis->spin(axis3 + axis4, axis3 - axis4); 

        delay(20);
    }
}