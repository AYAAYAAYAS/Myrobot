/*
几个简易的循迹小车行走函数
*/
#include "main.h"

#include "simple_motor_example.h"

int limit(int data,int max)
{	
    if(data<-max) data=-max;	
    if(data> max) data= max;	
    return data;
}


void set_motor(int motor1,int motor2)
{
	motor1=-motor1;
	motor2=-motor2;
	//控制电机正反转
	if(motor1>0)
	{
		IN1(1);
		IN2(0);
	}
	else if(motor1<0)
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
//		motor1=myabs(motor1);
		PWM_1 = limit(motor1,MAX);
	}
	else
	{
		PWM_1 = 0;		
	}
		

	if(motor2)
	{
//		motor2=myabs(motor2);
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






