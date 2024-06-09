#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
//#include "PWM_Moter.h"
//#include "encode.h"
#include "timer.h"
////#include "ANO.h"
//#include "pid.h"
////#include "menu.h"
////#include "menu_key.h"
#include "Serial.h"
//#include "mydma.h"
#include "openmv.h"

#define W 320
#define H 240
extern _User_USART openmv;
extern uint8_t Serial_RxData;
extern uint8_t Serial_RxFlag;
//int  Angle;
//float speed_L;
//float speed_R;
//int Timer_count;
//int pwmspeed1;
//int pwmspeed2;
//extern _pid pid_speed;

//uint16_t MenuFlag;

uint16_t avg[W][H];
uint16_t central_point;
void Servo_control();
int main(void)
{
	Init_TIM1();
//	Init_TIM2();
//	Init_TIM4();
	Serial_Init();
//	cmd_Init();
	OLED_Init();
//	menu_key_Init();
	TIM_SetCompare4(TIM1,Servo_SetAngle(0));
	while(1)
	{			
//		MenuFlag=menu();
//		if(MenuFlag==2)
//		{
//			axis();
//		}
//			
			OLED_ShowNum(1,1,openmv.X, 3);
			OLED_ShowNum(2,1,openmv.Y, 3);
//			OLED_ShowNum(3,1,openmv.W, 3);
//			OLED_ShowNum(4,1,openmv.H, 3);
//			Delay_ms(500);
//			MyDMA_Transfer();
//			pid_x(openmv.X);
			 Servo_control();
			Delay_ms(5000);
//	 if(speed_L<2.9)pwmspeed1+=1;//限制速度可修改pwm变化速率达到调参顺滑
//   if(speed_L>3.1)pwmspeed1-=1;
//   if(speed_R<2.9)pwmspeed2+=1;
//   if(speed_R>3.1)pwmspeed2-=1;
//		set_pwm(pid_speed_realize(&pid_speed,speed_L),pid_speed_realize(&pid_speed,speed_R));
//		Serial_Printf("speed2=%.2f\r\n",speed_L);
//		Serial_Printf("speed1=%.2f\r\n",speed_R);
//		Delay_ms(100);
//		//电机速度等信息发送到 上位机
//		//注意上位机不支持浮点数，所以要乘100
//		sent_data(speed_L*100,3.0*100,speed_R*100,3*100);
	}
}
//定时中断获取当前速度
//void TIM1_UP_IRQHandler()
// {
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)== SET)
//	{
//		Timer_count++;
//		if(Timer_count%5==0)
//		{
//			speed_L=Get_Speed(2);
//			speed_R=Get_Speed(4);
//			Timer_count=0;
//		}
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}	
// }
 
/*void TIM2_IRQHandler()
 {
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)== SET)
	{
		
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
 }*/
 
void Servo_control()
{
	if(openmv.X==0x01)
	{
		TIM_SetCompare1(TIM1,Servo_SetAngle(90));
		TIM_SetCompare4(TIM1,Servo_SetAngle(90));
		Delay_ms(1000);
		TIM_SetCompare1(TIM1,Servo_SetAngle(180));
		TIM_SetCompare4(TIM1,Servo_SetAngle(180));
	}
//	else
//	{
//		TIM_SetCompare4(TIM1,Servo_SetAngle(0));
//		TIM_SetCompare1(TIM1,Servo_SetAngle(0));
//	}
}	
 
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		
		Serial_RxData= USART_ReceiveData(USART1);
		openmv_receive(Serial_RxData);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
} 
