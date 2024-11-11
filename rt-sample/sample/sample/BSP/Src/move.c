//
// Created by Administrator on 2024/5/10.
//
#include "stm32f4xx_hal.h"
#include "gpio.h"
void left_wheel(int in1,int in2){
    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, in1);
    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, in2);
}
void right_wheel(int in3,int in4){
    HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, in3);
    HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, in4);
}
void forward(){
    left_wheel(1,0);
    right_wheel(1,0);
}
void turnleft(){
    left_wheel(1,1);
    right_wheel(1,0);
}
void turnright(){
    left_wheel(1,0);
    right_wheel(1,1);
}
void stop(){
    left_wheel(0,0);
    right_wheel(0,0);
}