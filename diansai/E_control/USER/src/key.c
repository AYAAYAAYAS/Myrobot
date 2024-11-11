
#include "main.h"
uint8_t key1_state = 0;																// 按键动作状态
uint8_t key1_state_last = 0;															// 上一次按键动作状态
uint8_t key1_flag=0;                                //   1按下，松开0
uint8_t key1_count=0;
uint8_t
uint8_t key2_state = 0;																// 按键动作状态
uint8_t key2_state_last = 0;															// 上一次按键动作状态
uint8_t key2_flag=0;                                //   1按下，松开0
uint8_t key2_count=0;
uint8_t
uint8_t key3_state = 0;																// 按键动作状态
uint8_t key3_state_last = 0;															// 上一次按键动作状态
uint8_t key3_flag=0;                                //   1按下，松开0
uint8_t key3_count=0;
uint8_t
uint8_t key4_state = 0;																// 按键动作状态
uint8_t key4_state_last = 0;															// 上一次按键动作状态
uint8_t key4_flag=0;                                //   1按下，松开0
uint8_t key4_count=0;

int  key1_can(void)
{
	      key1_state_last = key1_state;
		    key1_state = HAL_GPIO_ReadPin(KEY1_PORT,KEY1_PIN);
				if(key1_state && !key1_state_last)   
				{					
					key1_flag = 1;
		      return  1;
				}
	else 
		return 0;
}

int  key2_can(void)
{
	      key2_state_last = key2_state;
		    key2_state =  HAL_GPIO_ReadPin(KEY3_PORT,KEY3_PIN);
				if(key2_state && !key2_state_last)   
				{					
					key2_flag = 1;
		      return  1;
				}
	else 
		return 0;
}


int  key3_can(void)
{
	      key3_state_last = key3_state;
		    key3_state =  HAL_GPIO_ReadPin(KEY3_PORT,KEY3_PIN);
				if(key3_state && !key3_state_last)   
				{					
					key3_flag = 1;
		      return  1;
				}
	else 
		return 0;
}

int  key4_can(void)
{
	      key4_state_last = key4_state;
		    key4_state = HAL_GPIO_ReadPin(KEY4_PORT,KEY4_PIN);
				if(key4_state && !key4_state_last)   
				{					
					key4_flag = 1;
		      return  1;
				}
	else 
		return 0;
}