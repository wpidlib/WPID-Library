#include "main.h"
#include <iostream>

int printAngle(){
    while(1){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);
        //Brain.Screen.print("Angle: %f", fourbar->getPosition(deg));
        this_thread::sleep_for(25);
    }
    return 0;
}

void auton(){
  //thread printAngleThread = thread(printAngle);
  // fourbar->moveAbsolute(60, 70);
  // fourbar->moveAbsolute(110, 60);
  // fourbar->moveAbsolute(0, 70);

  chassis->strafe(24,40);
  chassis->turn(90,35);
  chassis->diagonal(-24, -24, 40);
  chassis->turn(-90,35);
  chassis->straight(-24,40);
}