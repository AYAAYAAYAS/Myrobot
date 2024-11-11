#ifndef __CONTROL_COM_LINK_H
#define __CONTROL_COM_LINK_H


#include "main.h"

union ReceiveData{
    short d;
    unsigned char data[2];
};

union SendData{
    short d;
    unsigned char data[2];
};

//联合体处理接收数据以及发送数据
typedef struct{
    int a;
  
    union SendData left_vel_get;
    union SendData right_vel_get;
    union SendData angle_get;
    union SendData SERVO_get;
    
    union ReceiveData left_vel_now;
    union ReceiveData right_vel_now;
    union ReceiveData angle_now ;
    union ReceiveData SERVOX_now ;
    union ReceiveData SERVOY_now;
}DATA_HANDLE;

void COM_Receive_ROBOT(uint16_t Com_Data);
void COM_Receive_SERVO(uint16_t Com_Data);


#endif 
