#ifndef _MOTOR_H
#define _MOTOR_H

#include "tim.h"

//定义L298N上的4个逻辑输入口
#define IN1(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,1):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,0);}while(0);
#define IN2(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,1):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,0);}while(0);
#define IN3(x)  do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0);}while(0);
#define IN4(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,1):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,0);}while(0);

void forward(void);
void turnleft(void);
void turnright(void);
void stop(void);
void ENA(int x);
void ENB(int x);
#endif
