#ifndef __SERVO_H
#define __SERVO_H

#define Servo_X TIM1->CCR1
#define	Servo_Y TIM1->CCR2

void Servo_SetAngleX(float Angle_x);
void Servo_SetAngleY(float Angle_y);
void Servo_Init(void);


#endif
