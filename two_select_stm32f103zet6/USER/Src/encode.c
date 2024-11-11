#include "main.h"

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
/**************************************************************************
Function: Read encoder count per unit time
Input   : TIMX：Timer
Output  : none
函数功能：单位时间读取编码器计数
入口参数：TIMX：定时器
返回  值：编码器脉冲值
**************************************************************************/
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

/**************************************************************************
功    能: 计算实际转速
输    入: encoder_cnt：脉冲数；ppr：码盘数；ratio：减速比；cnt_time：计数时间(ms)
返回  值: 车轮转速 rpm
********************                       ******************************************************/
float Moto_Speed(int encoder_cnt,uint16_t ppr,uint16_t ratio)
{
    encoder_cnt = myabs(encoder_cnt);  
    return encoder_cnt*100/4/ppr/ratio;    /* 4倍频 */   
}

/**************************************************************************
功    能: 计算转数对应编码器脉冲数
输    入: num：转数；ppr：码盘数；ratio：减速比
返 回 值: 电机脉冲数 
**************************************************************************/
long Num_Encoder_Cnt(float num,uint16_t ppr,float ratio)
{
    return (num*ratio*ppr*4);                               /* 4倍频 */       
}

/**************************************************************************
功    能: 计算转速对应编码器脉冲数
输    入: rpm：转速；ppr：码盘数；ratio：减速比；cnt_time：计数时间(ms)
返 回 值: 电机脉冲数 
**************************************************************************/
long Rpm_Encoder_Cnt(float rpm,uint16_t ppr,uint16_t ratio,uint16_t cnt_time)
{
    return (rpm*ratio*ppr*4)/(60*1000/cnt_time);            /* 4倍频 */       
}
