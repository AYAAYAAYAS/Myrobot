#ifndef __COMSERIAL_H
#define __COMSERIAL_H

#include "main.h"

void UsartRxToBuf(uint8_t data);
void Usartdata_up(short leftspeed, short rightspeed,short angle,unsigned char Flag);
extern float a[3],w[3],angle[3],T;
extern float roll,gyrox,gyroz;
extern com_data Recdata,Sendata;

#endif 
