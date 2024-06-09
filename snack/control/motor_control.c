#include "timer.h"
#include "motor_control.h"


//int pwmspeed1;
//int pwmspeed2;
	/*************늙C��*******************/
void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void set_motor(int motor1,int motor2)
{
/************���õ��ת������***************/
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
		
/************���õ���ٶ��ٶ�***************/
/***���1***/		
	if(motor1<0)
	{
		if(motor1<-99)//�޷�
		{	
			motor1=-99;
			TIM_SetCompare4(TIM1,motor1+100);
		}
	}
	else
		{
			if(motor1>99)
			{
				motor1=99;
				TIM_SetCompare4(TIM1,motor1);
			}
		}
		
/***���2***/	
	if(motor1<0)
	{
		if(motor2<-99)//�޷�
		{	
			motor2=-99;
			TIM_SetCompare1(TIM1,motor2+100);
		}
	}
	else
	{
		if(motor2>99)
		{
			motor2=99;
			TIM_SetCompare1(TIM1,motor2);
		}
	}
}	
/*���ٺ���
if(Get_Speed(2)<2.9)pwmspeed1++��
if(Get_Speed(2)>3.1)pwmspeed1--��
if(Get_Speed(4)<2.9)pwmspeed1++��
if(Get_Speed(4)>3.1)pwmspeed1--��*/