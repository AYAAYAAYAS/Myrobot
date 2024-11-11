#include "main.h"

void Angel_Set(SVO SERVO_SELECT,float ANGEL,int Speed){
  int COMPARE = 500+(ANGEL/120)*2000;
  switch(SERVO_SELECT){
    case SERVO_X:TIM2->CCR1 = COMPARE;break;
    case SERVO_Y:TIM2->CCR2 = COMPARE;break;
  }
}


