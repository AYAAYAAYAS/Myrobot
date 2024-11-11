//
// Created by Administrator on 2024/5/10.
//

#ifndef CONTROL_COM_LINK_H
#define CONTROL_COM_LINK_H


union ReceiveData{
    short d;
    unsigned char data[2];
}left_vel_now,right_vel_now,angle_now;

union SendData{
    short d;
    unsigned char data[2];
}left_vel_get,right_vel_get,angle_get;

#endif //CONTROL_COM_LINK_H
