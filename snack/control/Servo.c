#include "stm32f10x.h"                  // Device header
int Servo_SetAngle(float Angle)
{
	int a=Angle / 180 * 2000 +500;
	return a;

}




