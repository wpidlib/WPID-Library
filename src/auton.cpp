#include "main.h"
#include <iostream>

void auton(){
  chassis->setMaxAcceleration(1);
  chassis->straight(24, 50);
}
