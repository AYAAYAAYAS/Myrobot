/*
�������׵�ѭ��С�����ߺ���
*/

#include "simple_motor_example.h"
#include "pid.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static int Moto_L = 0 , Moto_R = 0; 
    if (htim->Instance == TIM2)
    {
        Reality_Velocity[0] = Read_Encoder(4);                     /* ��ȡʵ��������--���� */  
				Reality_Velocity[1] = Read_Encoder(5);										/* ��ȡʵ��������--���� */ 
			
        Reality_Position[0] += Reality_Velocity[0];                   /* ʵ��λ�������� */
        
        Moto_L = Position_PID(Reality_Position[0],Target_Position[0]);  /* λ��ʽλ�ÿ��� */        
        Moto_L = limit(Moto_L,Target_Velocity[0]);                    /* λ�û�����޷� */
        
        Moto_L = Incremental_PID(Reality_Velocity[0],Moto_L);      /* ����ʽ�ٶȿ��� */
			
			
        Reality_Position[1] += Reality_Velocity[1];                   /* ʵ��λ�������� */
        
        Moto_R = Position_PID(Reality_Position[1],Target_Position[1]);  /* λ��ʽλ�ÿ��� */        
        Moto_R = limit(Moto_L,Target_Velocity[1]);                    /* λ�û�����޷� */
        
        Moto_R = Incremental_PID(Reality_Velocity[1],Moto_R);      /* ����ʽ�ٶȿ��� */
        set_motor(Moto_L,Moto_R);                                      /* ��ֵ */
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
	//���Ƶ������ת
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
		
//�޷�
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






