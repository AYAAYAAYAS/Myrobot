#ifndef __MOTRO_H	
#define __MOTRO_H
#include "stm32f10x.h"                  // Device header

#define  IN1(x)   do{x?HAL_GPIO;}while(0)
#define  IN2(x)   do{x?;}while(0)
#define  IN3(x)   do{x?;}while(0)
#define  IN4(x)	  do{x?;}while(0)

void Motor_Init(void);
void set_motor(int motor1,int motor2);


#endif	
