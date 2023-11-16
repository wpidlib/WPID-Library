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
  //thread disp = thread(printAngle);
  for (size_t i = 0; i < 4; i++){
    chassis->straight(10,40);
    //chassis->waitUntilSettled();
    chassis->turn(90,20);
    //chassis->waitUntilSettled();
    //chassis->waitUntilSettled();
    // chassis->waitUntilSettled();
    // std::cout << "Finished straight" << std::endl;
    // chassis->turn(90,30);
    // std::cout << std::endl;
  }
}
