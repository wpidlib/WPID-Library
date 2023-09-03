#include "main.h"

void pre_auton(){
    init();
}

void usercontrol(){
    while (1) {
        Brain.Screen.clearScreen();
        chassis->spin(con->Axis3.value());
    }
    
}

int main() {
    pre_auton();
}










