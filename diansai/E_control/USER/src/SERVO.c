#include "main.h"
#define PI 3.14159265
extern DATA_HANDLE data_handle;
float angel_x,angel_y;
void Angel_Set(SVO SERVO_SELECT,float ANGEL){
  int COMPARE = 500+(ANGEL/180)*2000;
  switch(SERVO_SELECT){
    case SERVO_X:TIM2->CCR1 = COMPARE;break;
    case SERVO_Y:TIM2->CCR2 = COMPARE;break;
  }
}
float trace(float x)
{
  float bias = (x-320)*100;
  angel_x=atanf(bias/640*100)*(180.0/PI);
  return angel_x;
}


