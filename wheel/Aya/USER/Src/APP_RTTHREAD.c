#include "rtthread.h"
#include "APP_RTTHREAD.h"
#include "stdio.h"
#include "main.h"
#include "usart.h"
struct rt_thread MPU6050_thread;
struct rt_thread Serial_thread; 
struct rt_thread Servo_thread;

extern float theta_err,rho_err;
extern uint8_t cmd;
int16_t AX,AY,AZ,GX,GY,GZ;
uint8_t ID; 
uint8_t speed_L,speed_R;
//extern uint8_t buffer_1_i,buffer_1_f,buffer_2_i,buffer_2_f,buffer_3;
//extern int Target_Velocity_L,Target_Velocity_R
//    ,Reality_Velocity_L,Reality_Velocity_R;   
//extern int Target_Position_L,Target_Position_R
//    ,Reality_Position_L,Reality_Position_R; 

rt_uint8_t MPU6050_thread_stack[128];
rt_uint8_t Servo_thread_stack[128];
rt_uint8_t Serial_thread_stack[128];



void Serial_task_entry(void *parameter) 
{
		char tx_data[] = "Hello, RT-Thread!";
    char rx_data[50];

    while (1)
    {
       HAL_UART_Transmit(&huart1, (uint8_t*)tx_data, sizeof(tx_data), HAL_MAX_DELAY);
       HAL_UART_Receive(&huart1, (uint8_t*)rx_data, sizeof(rx_data), HAL_MAX_DELAY);
       rt_thread_mdelay(10);
    }
}

//MPU6050任务
 void MPU6050_task_entry(void *parameter)
{
	OLED_Clear();
	while(1)
	{
//		OLED_ShowNum(1,1,buffer_1_i,3);

//		OLED_ShowNum(2,1,buffer_2_i,3);
		OLED_ShowNum(2,6,1,3);
//		OLED_ShowNum(3,1,TIM1->CCR2 ,2);
//		OLED_ShowNum(3,4,TIM1->CCR1 ,2);
//		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
//		OLED_ShowSignedNum(2, 1, AX, 5);
//		OLED_ShowSignedNum(3, 1, AY, 5);
//		OLED_ShowSignedNum(4, 1, AZ, 5);
//		OLED_ShowSignedNum(2, 8, GX, 5);
//		OLED_ShowSignedNum(3, 8, GY, 5);
//		OLED_ShowSignedNum(4, 8, GZ, 5);
		rt_thread_mdelay(20);
	}
}

void Servo_task_entry(void *parameter)
{
	PID_Init(2,0.03,0.01,5,0.1,0.25);
	while(1)
	{
      HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
    		rt_thread_mdelay(10);
	}
}

//初始化线程函数
void MX_RT_Thread_Init(void)
{
	rt_thread_init(&MPU6050_thread,"MPU6050",MPU6050_task_entry,RT_NULL,&MPU6050_thread_stack[0],sizeof(MPU6050_thread_stack),5,20);
	rt_thread_startup(&MPU6050_thread);
	rt_thread_init(&Servo_thread,"Servo",Servo_task_entry,RT_NULL,&Servo_thread_stack[0],sizeof(Servo_thread_stack),6,20);
	rt_thread_startup(&Servo_thread);
	rt_thread_init(&Serial_thread,"Serial",Serial_task_entry,RT_NULL,&Serial_thread_stack[0],sizeof(Serial_thread_stack),7,20);
//	rt_thread_startup(&Serial_thread);
}