#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"
int myabs(int x);
int16_t Read_Encoder(uint8_t TIMX);
float Moto_Speed(int encoder_cnt,uint16_t ppr,uint16_t ratio);
long Num_Encoder_Cnt(float num);
long Distance_Counter(float num);
long Speed_V(float rpm);

#endif
