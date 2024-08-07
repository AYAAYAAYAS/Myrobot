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

/****l298n******/
//void set_motor(int motor1,int motor2)
//{
//	motor1=-motor1;
//	motor2=-motor2;
//	//控制电机正反转
//	if(motor1>0)
//	{
//		IN1(1);
//		IN2(0);
//	}
//	else if(motor1<0)
//	{
//		IN1(0);
//		IN2(1);
//	}
//	if(motor2>0)
//	{
//		IN3(1);
//		IN4(0);
//	}
//		else
//		{
//			IN3(0);
//		  IN4(1);
//		}	
//		
////限幅
//	if(motor1)
//	{
//		motor1=abs(motor1);
//		PWM_1 = limit(motor1,MAX);
//	}
//	else
//	{
//		PWM_1 = 0;		
//	}
//		

//	if(motor2)
//	{
//		motor2=abs(motor2);
//		PWM_2 = limit(motor2,MAX);
//	}
//	else
//	{
//		PWM_2 = 0;
//	}
//}	

//void Moto_Stop(void)
//{
//    IN1(0);
//    IN2(0);
//    IN3(0);
//    IN4(0);
//    PWM_1=0;
//    PWM_2=0;   
//}




void AO_Control_L(uint32_t AIN1,uint32_t AIN2)
{
				PWM_1=AIN1;
				PWM_2=AIN2;

}
void AO_Control_R(uint32_t BIN1,uint32_t BIN2)
{
				PWM_3=BIN1;
				PWM_4=BIN2;
}
void motor_control(int L_speed, int R_speed)
{
    if (L_speed > 0)
    {
        AO_Control_L(L_speed, MAX); 
    }
    else if (L_speed <= 0)
    {
        AO_Control_L(MAX,-L_speed); 
    }


    // 控制右电机
    if (R_speed > 0)
    {
        AO_Control_R(R_speed, MAX);  
    }
    else if (R_speed <= 0)
    {
        AO_Control_R(MAX, -R_speed);  
    }
}

void motor_STOP()
{
	AO_Control_R(MAX,MAX);
	AO_Control_L(MAX,MAX);	
}

//void forward()
//{
//					DL_TimerG_setCaptureCompareValue(PWM_L_INST,1000,GPIO_PWM_L_C0_IDX);
//				DL_TimerG_setCaptureCompareValue(PWM_L_INST,300,GPIO_PWM_L_C1_IDX);
//					DL_TimerG_setCaptureCompareValue(PWM_R_INST,300,GPIO_PWM_R_C0_IDX);
//				DL_TimerG_setCaptureCompareValue(PWM_R_INST,1000,GPIO_PWM_R_C1_IDX);
//}


