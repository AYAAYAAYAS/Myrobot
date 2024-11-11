#include "main.h"
//此处定义要处理的数据
#define SERVORUN
//接收获取到的数据
uint8_t RX_BUFFER[20];
//recevie
DATA_HANDLE data_handle;
#ifdef ROBOTRUN
void COM_Receive_ROBOT(uint16_t Com_Data){
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
        while((USART1->SR) & 0x40);
        USART1->DR =(uint8_t)*data++;
    }
}

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
#endif

#ifdef SERVORUN
  void COM_Receive_SERVO(uint16_t Com_Data){
    static uint8_t RxState = 0;
    static uint8_t RxCount = 0;
    
    if(!(RX_BUFFER[0] == 0xa1)){
        RxCount=0;
        RX_BUFFER[0]=0;
    }
    if(RxCount>=10){
        if(RxState == 0 && Com_Data == 0xa1){
            RxState = 1;
            RX_BUFFER[RxCount++] = 0xa1;
        }
        else if(RxState == 1 && Com_Data == 0xa2){
            RxState = 2;
            RX_BUFFER[RxCount++] = 0xa2;
        }
        else if(RxState == 2){
            RX_BUFFER[RxCount++]=Com_Data;
            if(RxCount >= 7 || Com_Data == 0x5B){
              RxState = 3;
              data_handle.SERVOX_now.data[0]=RX_BUFFER[3];
              data_handle.SERVOX_now.data[1]=RX_BUFFER[4];
              data_handle.SERVOY_now.data[0]=RX_BUFFER[5];
              data_handle.SERVOY_now.data[1]=RX_BUFFER[6]; 
            }

        }
        else if(RxState == 3){
          if(RX_BUFFER[7] == 0x5B){       
            RxCount=0;
            RX_BUFFER[0]=0;
          }
          else{
            for(int i=0;i<8;i++) RX_BUFFER[i]=0x00;
          }
        }
    }
  
  }
#endif
