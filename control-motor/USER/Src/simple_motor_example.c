/*
�������׵�ѭ��С�����ߺ���
*/

#include "simple_motor_example.h"

//����ʹ��ͨ��A,B
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


//��������ת��
//ǰ��
void forward(void){
    
    IN1(1);
    IN2(0);
    IN3(1);
    IN4(0);
    ENA(300);
    ENB(300);
}

//��ת
void turnleft(void){
    IN1(1);
    IN2(0);
    IN3(0);
    IN4(0);
    ENA(400);
    ENB(0);
}

//��ת

void turnright(void){
    IN1(0);
    IN2(0);
    IN3(1);
    IN4(0);
    ENA(0);
    ENB(400);
}
//ֹͣ
void stop(void){
    IN1(1);
    IN2(1);
    IN3(1);
    IN4(1);
    ENA(0);
    ENB(0);
}

