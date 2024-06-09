#include "stm32f10x.h"                  // Device header
#include "timer.h"
void set_pwm(uint16_t motor1,uint16_t motor2)
{
	TIM_SetCompare1(TIM1,motor1);
	TIM_SetCompare4(TIM1,motor2);
	
}	