//
// Created by Administrator on 2024/5/10.
//
//
// Created by Administrator on 2024/5/10.
//
#include "usart.h"
#include "com_link.h"

uint8_t RX_BUFFER[20];
void COM1_Receive(int16_t Com_Data){
    static uint8_t RxState = 0;
    static uint8_t RxCount = 0;
    RX_BUFFER[RxCount++]=Com_Data;
    if(!(RX_BUFFER[0 == 0xa1])){
        RxCount=0;
        RX_BUFFER[0]=0;
    }

    if(RxCount>=10){

        if(RxState == 0 && RX_BUFFER[0] == 0xa1){
            RxState = 1;
            RX_BUFFER[0] = 0xa1;
        }
        else if(RxState == 1 && RX_BUFFER[1] == 0Xa2){
            RxState = 2;
            RX_BUFFER[1] = 0xa2;
        }
        else if(RxCount == 2){
            left_vel_get.data[0]=RX_BUFFER[3];
            left_vel_get.data[1]=RX_BUFFER[4];

            right_vel_get.data[0]=RX_BUFFER[5];
            right_vel_get.data[1]=RX_BUFFER[6];
        }

        RxCount=0;
        RX_BUFFER[0]=0;
    }

}

uint8_t Usart_Tx(uint8_t *data,uint8_t len){
    while(len--){
        while((USART1->SR&0x40==0));
        USART1->DR =(uint8_t)*data++;
    }
}
//´®¿Ú·¢ËÍ
uint8_t  TX_BUFFER[13];
void COM1_Send(short leftspeed, short rightspeed,short angle, unsigned char Flag){
    left_vel_now.d = leftspeed;
    right_vel_now.d = rightspeed;
//    angle_now = angle*88;
    TX_BUFFER[0]=0xa1;
    TX_BUFFER[1]=0xa2;
    TX_BUFFER[2]=5;
    TX_BUFFER[3]=left_vel_now.data[0];
    TX_BUFFER[4]=left_vel_now.data[1];
    TX_BUFFER[5]=right_vel_now.data[0];
    TX_BUFFER[6]=right_vel_now.data[1];
    TX_BUFFER[7]=angle_now.data[0];
    TX_BUFFER[8]=angle_now.data[1];
    TX_BUFFER[9]=Flag;
    TX_BUFFER[10]=0xa3;
    TX_BUFFER[11]=0xa4;
    Usart_Tx(TX_BUFFER,12);
}