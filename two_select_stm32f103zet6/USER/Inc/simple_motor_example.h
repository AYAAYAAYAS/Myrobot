#ifndef _MOTOR_H
#define _MOTOR_H

#include "main.h"
#include "encode.h"
//定义L298N上的4个逻辑输入口
#define IN1(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,RESET);}while(0);
#define IN2(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,RESET);}while(0);
#define IN3(x)  do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,RESET);}while(0);
#define IN4(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,RESET);}while(0);

#define dead_veltage 20
#define MAX 200
#define PWM_1 TIM3->CCR1 
#define PWM_2	TIM3->CCR2

extern int Target_Velocity[2],Reality_Velocity[2];   
extern int Target_Position[2],Reality_Position[2]; 
void Moto_Stop(void);
void set_motor(int motor1,int motor2);
int limit(int data,int max);

#endif
