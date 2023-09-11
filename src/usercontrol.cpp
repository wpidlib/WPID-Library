#include "main.h"

// cubes value and returns as a proportion
double scale(double x) {
    return (x > 0 ? 100 : -100) * ((x/127) * (x/127)); 
}

void usercontrol(){
    chassis->forward(12, 25);
    chassis->forward(-12, 35);

    chassis->turn(-90, 20);
    delay(2000);
    //chassis->turn(90, 20);
    
    // axis values on controller
    double axis3, axis4 = 0;
    while (1) {
        axis3 = scale(con->Axis3.value());
        axis4 = scale(con->Axis4.value());
        chassis->spin(axis3 + axis4, axis3 - axis4); 

        delay(20);
    }
}