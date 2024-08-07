#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"
int16_t Read_Encoder(uint8_t TIMX);
float Moto_Speed(int encoder_cnt);
long Num_Encoder_Cnt(float num);
long Rpm_Encoder_Cnt(float rpm,uint16_t cnt_time);

#endif
