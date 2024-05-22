#ifndef _MOTOR_H
#define _MOTOR_H

#include "main.h"
#include "pid.h"
//定义L298N上的4个逻辑输入口
#define IN1(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,RESET);}while(0);
#define IN2(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,RESET);}while(0);
#define IN3(x)  do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,RESET);}while(0);
#define IN4(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,RESET);}while(0);
 
#define MAX 100
#define PWM_1 TIM3->CCR1 
#define PWM_2	TIM3->CCR2

extern int Target_Velocity_L,Target_Velocity_R
						,Reality_Velocity_L,Reality_Velocity_R;   
extern int Target_Position_L,Target_Position_R
						,Reality_Position_L,Reality_Position_R;   
void Moto_Stop(void);
void set_motor(int motor1,int motor2);
int limit(int data,int max);

#endif
