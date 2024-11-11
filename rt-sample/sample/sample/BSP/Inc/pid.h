#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"                  // Device header

//#include "main.h"
//#include "tim.h"

typedef struct
{
 float target; //目标值
 float reality;//实际值
 float Bias; //偏差值
 float Last_Bias;//上一偏差值
 float Position_kp, Position_ki, Position_kd;//pid系数
 float Intergal_Bias;//偏差累计
}Position_pid;//位置式PID参数

typedef struct
{
 float target; //目标值
 float reality;//实际值
 float Bias; //偏差值
 float Last_Bias;//上一偏差值
 float Prev_Bias;
 float Incremental_kp, Incremental_ki,Incremental_kd;//pid系数
}Incremental_pid;//增量式PID参数


extern float angle_x;
extern float anglex;

void PID_Init(float P_kp ,float P_ki ,float P_kd ,float P_kp ,float I_kp ,float I_ki ,float I_kd);
int limit_(float Data,float max);
int Position_PID(float Reality,float Target);
int Incremental_PID(float Reality,float Target);
//float p_speed_realize(_pid*pid,float actual_val);
//float pi_speed_realize(_pid*pid,float actual_val);
	
#endif
