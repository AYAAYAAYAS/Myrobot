#include "stm32f10x.h"                  // Device header
#include "Delay.h"
                                                                                                                                                                                                    

void menu_key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//��ʱ��
	GPIO_InitTypeDef GPIO_InitStruture;
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStruture.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; //���ö˿�
	GPIO_Init(GPIOB,&GPIO_InitStruture);

}	

int key_read()
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0);
		Delay_ms(20);
		KeyNum = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0);
		Delay_ms(20);
		KeyNum = 3;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)
	{
		Delay_ms(5);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0);
		Delay_ms(5);
		KeyNum = 4;
	}
	return KeyNum;

}

