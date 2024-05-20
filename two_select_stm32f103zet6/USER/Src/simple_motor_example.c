/*
几个简易的循迹小车行走函数
*/

#include "simple_motor_example.h"
#include "pid.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static int Moto_L = 0 , Moto_R = 0; 
    if (htim->Instance == TIM2)
    {
        Reality_Velocity[0] = Read_Encoder(4);                     /* 获取实际脉冲数--左轮 */  
				Reality_Velocity[1] = Read_Encoder(5);										/* 获取实际脉冲数--右轮 */ 
			
        Reality_Position[0] += Reality_Velocity[0];                   /* 实际位置脉冲数 */
        
        Moto_L = Position_PID(Reality_Position[0],Target_Position[0]);  /* 位置式位置控制 */        
        Moto_L = limit(Moto_L,Target_Velocity[0]);                    /* 位置环输出限幅 */
        
        Moto_L = Incremental_PID(Reality_Velocity[0],Moto_L);      /* 增量式速度控制 */
			
			
        Reality_Position[1] += Reality_Velocity[1];                   /* 实际位置脉冲数 */
        
        Moto_R = Position_PID(Reality_Position[1],Target_Position[1]);  /* 位置式位置控制 */        
        Moto_R = limit(Moto_L,Target_Velocity[1]);                    /* 位置环输出限幅 */
        
        Moto_R = Incremental_PID(Reality_Velocity[1],Moto_R);      /* 增量式速度控制 */
        set_motor(Moto_L,Moto_R);                                      /* 赋值 */
    }
}
int limit(int data,int max)
{	
    if(data<-max) data=-max;	
    if(data> max) data= max;	
    return data;
}


void set_motor(int motor1,int motor2)
{
	//控制电机正反转
	if(motor1>0)
	{
		IN1(1);
		IN2(0);
	}
	else
	{
		IN1(0);
		IN2(1);
	}
		
	
	
	if(motor2>0)
	{
		IN3(1);
		IN4(0);
	}
		else
		{
			IN3(0);
		  IN4(1);
		}	
		
//限幅
	if(motor1)
	{
		motor1=abs(motor1)+dead_veltage;
		PWM_1 = limit(motor1,MAX);
	}
	else
	{
		PWM_1 = 0;		
	}
		

	if(motor2)
	{
		motor2=abs(motor2)+dead_veltage;
		PWM_2 = limit(motor2,MAX);
	}
	else
	{
		PWM_2 = 0;
	}
}	

void Moto_Stop(void)
{
    IN1(0);
    IN2(0);
    IN3(0);
    IN4(0);
    PWM_1=0;
    PWM_2=0;   
}






