#include "main.h"
int target_pwm;
int Servo_SetXAngle(float target_Angle)
{
	target_pwm=target_Angle / 180 * 2000 +500;
	return target_pwm;
}




