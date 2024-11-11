#include "main.h"
#include "tim.h"
#include "usart.h"

extern uint8_t RX_BUFFER[20];
//recevie
extern DATA_HANDLE data_handle;
extern uint8_t cmd;
extern uint8_t send_cmd;

#define MID_W 320
#define MID_H 320
int task_angel[3] = {servo_up,servo_mid,servo_down};
static void LED_1(void *param){


   
}

void MENU_SHOW(void *param){
}

void servo_task(){
 static int i;
//          i++;
    switch(i){
      
      case 0:{
          Angel_Set(SERVO_Y,trace(data_handle.SERVOX_now.data[0]));
          Angel_Set(SERVO_X,trace(data_handle.SERVOY_now.data[0]));
          break;
      }
      case 1: Angel_Set(SERVO_Y,task_angel[0]); Angel_Set(SERVO_X,task_angel[2]);break;
      case 2: Angel_Set(SERVO_Y,task_angel[0]); Angel_Set(SERVO_X,task_angel[1]);break;
      case 3: Angel_Set(SERVO_Y,task_angel[2]); Angel_Set(SERVO_X,task_angel[0]);break;
      case 4: Angel_Set(SERVO_Y,task_angel[2]); Angel_Set(SERVO_X,task_angel[2]);break;
  }
    if(i>4)i=0;
   HAL_Delay(1000);
}
void APPLY()
{
  servo_task();
}
