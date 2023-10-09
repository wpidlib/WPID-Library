#include "main.h"

void auton(){

  for(int i = 1; i <= 12; i++){
    chassis->forward(24,30);
    delay(5000);
    chassis->turn(90,20);
    delay(5000);
  } 
  delay(5000);
}

/**
 * @brief // for(int i = 0; i < 8; i++){
  //   chassis->forward(25,30);
  //   chassis->turn(-90,25);
  // }
 * 
 */