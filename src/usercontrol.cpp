#include "main.h"

// square a value
double sqr(double x) { return x * x; }
// returns a % of 127 * 100
double scale(double x) { return 100 * (sqr(x)/127); }

void usercontrol(){
    double axis3, axis4 = 0;
    while (1) {
        axis3 = scale(con->Axis3.value());
        axis4 = scale(con->Axis4.value());
        chassis->spin(axis3 + axis4, axis3 - axis4); 
        
        delay(20);
    }
}