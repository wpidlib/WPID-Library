#include "main.h"
#include <iostream>

void auton(){
  std::cout << "Setting Angle" << std::endl;
  fourbar->setAngle(90,10);
  wait(1000, msec);
}

  // chassis->strafe(24,20);
  // wait(1000, msec);
  // chassis->diagonal(-24,-24,20);