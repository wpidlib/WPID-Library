#include "main.h"
#include <iostream>

void auton(){
  chassis->setMaxAcceleration(1.5);
  chassis->straight(15, 30);
}