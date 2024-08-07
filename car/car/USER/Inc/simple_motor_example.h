#ifndef _MOTOR_H
#define _MOTOR_H

#include "main.h"
#include "pid.h"
//定义L298N上的4个逻辑输入口
//#define IN1(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,RESET);}while(0);
//#define IN2(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,RESET);}while(0);
//#define IN3(x)  do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,RESET);}while(0);
//#define IN4(x)	do{x?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,RESET);}while(0);
#define Read_Huidu_IO1	 (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_9) ==GPIO_PIN_SET?1:0)
#define Read_Huidu_IO2	 (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8) ==GPIO_PIN_SET?1:0)
#define Read_Huidu_IO3	 (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) ==GPIO_PIN_SET?1:0)
#define Read_Huidu_IO4	 (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14) ==GPIO_PIN_SET?1:0)
#define Read_Huidu_IO5	 (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) ==GPIO_PIN_SET?1:0)
#define Read_Huidu_IO6	 (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12) ==GPIO_PIN_SET?1:0)
 
#define MAX 3600
#define PWM_1 TIM3->CCR1 
#define PWM_2	TIM3->CCR2                                                                      
#define PWM_3 TIM3->CCR3 
#define PWM_4	TIM3->CCR4

extern int Target_Velocity_L,Target_Velocity_R
						,Reality_Velocity_L,Reality_Velocity_R;   
extern int Target_Position_L,Target_Position_R
						,Reality_Position_L,Reality_Position_R;   
void Moto_Stop(void);
//void set_motor(int motor1,int motor2);
int limit(int data,int max);
void motor_control(int L_speed, int R_speed);
void motor_STOP();
void AO_Control_R(uint32_t BIN1,uint32_t BIN2);
typedef struct 
{
	 short speed[2];
	 short angel;
	
}com_data;

#endif
