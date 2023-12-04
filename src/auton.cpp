#include "main.h"
#include <iostream>

int printAngle(){
    while(1){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print("Angle: %f", fourbar->getPosition(deg));
        this_thread::sleep_for(25);
    }
    return 0;
}

void auton(){
  thread printAngleThread = thread(printAngle);
  // chassis->straight(24, 75);
  // chassis->straight(-24, 75);
  // chassis->turn(90, 25);
  // chassis->turn(-90, 25);
  fourbar->moveAbsolute(60, 75);
  fourbar->moveAbsolute(90, 75);
  fourbar->moveAbsolute(0, 75);
}