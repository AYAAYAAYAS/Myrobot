#include "find_trace_GRAY.h"
#include "simple_motor_example.h"
#define left_sign HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)
#define right_sign HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)

//void trace_red_2(void){
//		int sign;
//    if(left_sign == 1 &&  right_sign == 1)sign=1;
//		if(left_sign == 0 &&  right_sign == 1)sign=2;
//		if(left_sign == 1 &&  right_sign == 0)sign=3;
//	
//	switch(sign){
//		case 1:forward();break;
//		case 2:turnleft();break;
//		case 3:turnright();break;
//	}		
//}
