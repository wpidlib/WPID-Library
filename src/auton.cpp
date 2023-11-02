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
  thread disp = thread(printAngle);
  fourbar->moveAbsolute(60, 20);
  fourbar->moveAbsolute(-10, 20);
  //fourbar->moveAbsolute(0, 20);
}

  // chassis->strafe(24,20);
  // wait(1000, msec);
  // chassis->diagonal(-24,-24,20);