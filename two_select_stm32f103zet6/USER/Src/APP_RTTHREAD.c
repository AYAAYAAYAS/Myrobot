#include "rtthread.h"
#include "APP_RTTHREAD.h"
#include "stdio.h"
#include "main.h"


struct rt_thread MPU6050_thread;
rt_uint8_t MPU6050_thread_stack[128];
void MPU6050_task_entry(void *parameter);

int16_t AX,AY,AZ,GX,GY,GZ;
uint8_t ID; 
 


 
//MPU6050任务
 void MPU6050_task_entry(void *parameter)
{

	while(1)
	{
		
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		rt_thread_mdelay(200);
	}
}


struct rt_thread Servo_thread;
rt_uint8_t Servo_thread_stack[128];
void Servo_task_entry(void *parameter);

void Servo_task_entry(void *parameter)
{
			Servo_Init();

	while(1)
	{
		ID = MPU6050_GetID();
		OLED_ShowHexNum(1, 4, ID, 2);
		Servo_SetAngleX(90);
		Servo_SetAngleY(90);
		rt_thread_mdelay(200);
	}
}

//初始化线程函数
void MX_RT_Thread_Init(void)
{
	//初始化线程
	rt_thread_init(&MPU6050_thread,"MPU6050",MPU6050_task_entry,RT_NULL,&MPU6050_thread_stack[0],sizeof(MPU6050_thread_stack),3,20);
	//开启线程调度
	rt_thread_startup(&MPU6050_thread);
	
	rt_thread_init(&Servo_thread,"Servo",Servo_task_entry,RT_NULL,&Servo_thread_stack[0],sizeof(Servo_thread_stack),4,20);
	
	rt_thread_startup(&Servo_thread);
}