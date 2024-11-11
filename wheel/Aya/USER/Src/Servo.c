#include "main.h"
#include "Servo.h"

void Servo_SetAngleX(float Angle_x)
{
	
	Servo_X=(Angle_x / 180 * 2000 + 500);
	
}                                                                               
void Servo_SetAngleY(float Angle_y)
{
	Servo_Y=(Angle_y / 180 * 2000 + 500);
}


void Servo_Init(void)
{
	Servo_SetAngleX(45);
	Servo_SetAngleY(45);
}


