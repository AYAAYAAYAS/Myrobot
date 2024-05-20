#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"
#include <math.h>
int Read_Encoder(uint8_t TIMX);
float Moto_Speed(int encoder_cnt,uint16_t ppr,uint16_t ratio,uint16_t cnt_time);
long Num_Encoder_Cnt(float num,uint16_t ppr,float ratio);
long Rpm_Encoder_Cnt(float rpm,uint16_t ppr,uint16_t ratio,uint16_t cnt_time);

#endif
