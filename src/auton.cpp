#include "main.h"
#include <iostream>

void auton(){
  fourbar->moveRelativeAsync(20, 20);
  chassis->setMaxAcceleration(1.5);
  chassis->straight(24, 45);
  fourbar->waitUntilSettled();
  chassis->turn(90, 25);
  fourbar->moveAbsoluteAsync(0, 20);
  chassis->straight(24, 20);
  fourbar->waitUntilSettled();
  chassis->setTimeout(2500);
  chassis->straightAsync(10, 30);
  fourbar->moveAbsoluteAsync(60, 25);
  chassis->waitUntilSettled();
  fourbar->waitUntilSettled();
}