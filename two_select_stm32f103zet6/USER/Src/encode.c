#include "encode.h"
/**************************************************************************
Function: Read encoder count per unit time
Input   : TIMX��Timer
Output  : none
�������ܣ���λʱ���ȡ����������
��ڲ�����TIMX����ʱ��
����  ֵ������������ֵ
**************************************************************************/
int Read_Encoder(uint8_t TIMX)
{
    int Encoder_cnt;    
    switch(TIMX)
    {
        case 4:  Encoder_cnt= (short)TIM4 -> CNT; TIM4 -> CNT=0; break;
        case 5:  Encoder_cnt= (short)TIM5 -> CNT; TIM5 -> CNT=0; break;		
        default: Encoder_cnt=0;
    }
    return Encoder_cnt;
}

/**************************************************************************
��    ��: ����ʵ��ת��
��    ��: encoder_cnt����������ppr����������ratio�����ٱȣ�cnt_time������ʱ��(ms)
����  ֵ: ����ת�� rpm
**************************************************************************/
float Moto_Speed(int encoder_cnt,uint16_t ppr,uint16_t ratio,uint16_t cnt_time)
{
    encoder_cnt = abs(encoder_cnt);  
    return (encoder_cnt/4/ppr/ratio)*(1000/cnt_time)*60;    /* 4��Ƶ */   
}

/**************************************************************************
��    ��: ����ת����Ӧ������������
��    ��: num��ת����ppr����������ratio�����ٱ�
�� �� ֵ: ��������� 
**************************************************************************/
long Num_Encoder_Cnt(float num,uint16_t ppr,float ratio)
{
    return (num*ratio*ppr*4);                               /* 4��Ƶ */       
}

/**************************************************************************
��    ��: ����ת�ٶ�Ӧ������������
��    ��: rpm��ת�٣�ppr����������ratio�����ٱȣ�cnt_time������ʱ��(ms)
�� �� ֵ: ��������� 
**************************************************************************/
long Rpm_Encoder_Cnt(float rpm,uint16_t ppr,uint16_t ratio,uint16_t cnt_time)
{
    return (rpm*ratio*ppr*4)/(60*1000/cnt_time);            /* 4��Ƶ */       
}
