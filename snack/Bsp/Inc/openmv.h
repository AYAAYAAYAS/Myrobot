#ifndef __OPENMV_H
#define __OPENMV_H

#define count 10

typedef struct 
{		
		int X;
		int	Y;
		int	W;
		int H;							//��������
		uint8_t RxBuffer[count];			//���ջ���	
}_User_USART;

void openmv_receive(int16_t Com_Data);

#endif
