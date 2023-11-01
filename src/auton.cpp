#include "main.h"
#include <iostream>

void auton(){
  //chassis->setTimeout(2000, msec);
  chassis->straight(12.0, 20);
  chassis->turn(90, 20);
}

  // chassis->strafe(24,20);
  // wait(1000, msec);
  // chassis->diagonal(-24,-24,20);