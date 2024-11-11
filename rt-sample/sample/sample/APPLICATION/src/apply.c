#include "main.h"
#include "tim.h"
#include "usart.h"
static struct rt_thread thread1;
static char stack1[1024];
static struct rt_thread thread_2;
static char stack2[1024];
static struct rt_thread thread_3;
static char stack3[1024];

extern uint8_t cmd;
extern uint8_t send_cmd;

int task_angel[3] = {servo_up,servo_mid,servo_down};
static void LED_1(void *param){
  static int i;
  while(1)
  {
    i++;
    switch(i){
      case 0: Angel_Set(SERVO_Y,task_angel[0],0); Angel_Set(SERVO_X,task_angel[0],0);break;
      case 1: Angel_Set(SERVO_Y,task_angel[0],0); Angel_Set(SERVO_X,task_angel[2],0);break;
      case 2: Angel_Set(SERVO_Y,task_angel[0],0); Angel_Set(SERVO_X,task_angel[0],0);break;
      case 3: Angel_Set(SERVO_Y,task_angel[2],0); Angel_Set(SERVO_X,task_angel[0],0);break;
      case 4: Angel_Set(SERVO_Y,task_angel[2],0); Angel_Set(SERVO_X,task_angel[2],0);break;
    }
    if(i>4) i = 0;
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
    
    rt_thread_mdelay(500);
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,0);
    
    rt_thread_mdelay(400);
  }
}

void MENU_SHOW(void *param){
  OLED_Init();
  while(1)
  { 
      rt_thread_mdelay(100);
  }
}

void servo_task(void *param){
  while(1){
    

    rt_thread_mdelay(100);
  }
}

//
void APP_init(){
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,1);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
    HAL_UART_Transmit(&huart1,&send_cmd,sizeof(send_cmd),1);
    HAL_UART_Receive_IT(&huart1,(void *)&cmd, 1);
}
void APPLY()
{
  rt_thread_init(&thread1,"thread1",LED_1,RT_NULL,&stack1[0],512,10,1000);
  rt_thread_startup(&thread1);
  rt_thread_init(&thread_2,"thread2",MENU_SHOW,RT_NULL,&stack2[0],1024,16,500);
  rt_thread_startup(&thread_2);
  rt_thread_init(&thread_3,"thread3",servo_task,RT_NULL,&stack3[0],1024,17,500);
  rt_thread_startup(&thread_3);
}
