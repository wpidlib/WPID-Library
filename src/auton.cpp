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
  chassis->straightAsync(20, 15);
  fourbar->moveAbsolute(60, 30);
  fourbar->moveAbsolute(0, 30);
  chassis->waitUntilSettled();
  // std::cout << "Moving" << std::endl;
  // fourbar->waitUntilSettled();
  // std::cout << "Stopped" << std::endl;
}
