#include "stm32f10x.h"                  // Device header

void Sensor_Init(void)
{
	RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=14;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_Initstructure;
	EXTI_Initstructure.EXTI_Line=EXTI_Line14;
	EXTI_Initstructure.EXTI_LineCmd=ENABLE;
	EXTI_Initstructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initstructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstructure);
}	

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		
		
		EXTI_ClearITPendingBit(EXTI_Line14);
	}

}	