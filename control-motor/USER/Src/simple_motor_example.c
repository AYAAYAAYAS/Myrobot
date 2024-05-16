/*
几个简易的循迹小车行走函数
*/

#include "simple_motor_example.h"

//定义使能通道A,B
void ENA(int x){
    if(x>500){
        x=500;
     __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,x);     
    }
}
void ENB(int x){
    if(x>500){
        x=500;
     __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,x);     
    }
}


//定义电机的转向
//前进
void forward(void){
    
    IN1(1);
    IN2(0);
    IN3(1);
    IN4(0);
    ENA(300);
    ENB(300);
}

//左转
void turnleft(void){
    IN1(1);
    IN2(0);
    IN3(0);
    IN4(0);
    ENA(400);
    ENB(0);
}

//右转

void turnright(void){
    IN1(0);
    IN2(0);
    IN3(1);
    IN4(0);
    ENA(0);
    ENB(400);
}
//停止
void stop(void){
    IN1(1);
    IN2(1);
    IN3(1);
    IN4(1);
    ENA(0);
    ENB(0);
}

