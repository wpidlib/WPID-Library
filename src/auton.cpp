#include "main.h"

void auton(){
   for(int i = 0; i < 4; i++){
     chassis->straight(24, 30);
     delay(1000);
     chassis->turn(90,20);
     delay(1000);
   }
   chassis->stop();
}