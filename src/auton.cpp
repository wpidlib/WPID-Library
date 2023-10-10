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