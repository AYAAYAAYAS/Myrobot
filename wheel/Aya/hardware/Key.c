
#include "gpio.h"



uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == 0)
	{
		Delay_ms(20);
		while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0);
		Delay_ms(20);
		KeyNum = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 0)
	{
		Delay_ms(20);
		while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	
	return KeyNum;
}
