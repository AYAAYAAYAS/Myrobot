#ifndef __OPENMV_H
#define __OPENMV_H

#define count 10

typedef struct 
{		
		int X;
		int	Y;
		int	W;
		int H;							//处理数据
		uint8_t RxBuffer[count];			//接收缓存	
}_User_USART;

void openmv_receive(int16_t Com_Data);

#endif
