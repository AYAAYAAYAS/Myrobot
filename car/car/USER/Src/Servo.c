#include "main.h"
#include "Servo.h"

void Servo_SetAngleX(float Angle_x)
{
	
	PWM_3=(Angle_x / 180 * 2000 + 500);
	
}                                                                               
void Servo_SetAngleY(float Angle_y)
{
	PWM_4=(Angle_y / 180 * 2000 + 500);
}


void Servo_Init(void)
{
	Servo_SetAngleX(90);
	Servo_SetAngleY(90);
}


