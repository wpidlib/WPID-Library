#include "main.h"

void auton(){
   for(int i = 0; i < 4; i++){
     chassis->straight(24, 30);
     wait(1000, msec);
     chassis->turn(90,20);
     wait(1000, msec);
   }
   chassis->stop();
}