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
  for (size_t i = 0; i < 4; i++){
    fourbar->moveAbsoluteAsync(60, 20);
    chassis->straight(10,20);
    fourbar->waitUntilSettled();
    fourbar->moveAbsolute(0, 20);
    chassis->straight(-10,20);
  }
}
