#ifndef __SERVO_H
#define __SERVO_H

#define servo_up 135
#define servo_mid 90
#define servo_down 45
typedef enum{
  SERVO_X,
  SERVO_Y
}SVO;


void Angel_Set(SVO SERVO_SELECT,float ANGEL,int Speed);

#endif