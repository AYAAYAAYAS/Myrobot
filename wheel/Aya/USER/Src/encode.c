#include "encode.h"
#define PPR 20 //分辨率
#define RADIO 13 //减速比
#define DR 0.045 //周长，单位m
#define PI 3.1415926 
//取绝对值函数
int myabs(int x)
{
	if(x<0)
	{
		return -x;
	}
	else
	{
		return x;
	}
}
//读取编码值
int16_t Read_Encoder(uint8_t TIMX)
{
    int Encoder_cnt;    
    switch(TIMX)
    {
        case 4:  Encoder_cnt= (short)TIM4 -> CNT; TIM4 -> CNT=0; break;
        case 5:  Encoder_cnt= -(short)TIM5 -> CNT; TIM5 -> CNT=0; break;		
        default: Encoder_cnt=0;
    }
    return Encoder_cnt;
}


float Moto_Speed(int encoder_cnt,uint16_t ppr,uint16_t ratio)
{
    encoder_cnt = myabs(encoder_cnt);  
    return encoder_cnt*100/4/ppr/ratio;    /* 4倍频 */   
}

//圈数读取
long Num_Encoder_Cnt(float num)
{
    return num/(RADIO*PPR*4);                               /* 4倍频 */       
}
//距离计算
long Distance_Counter(float num)
{
	return num*PI*DR;
}
//线速度 V=WR
long Speed_V(float rpm)
{
  int speed_w=rpm/(RADIO*PPR*4)*1000/10*60; //角速度 
  return speed_w/60 * PI * DR;
	
}

