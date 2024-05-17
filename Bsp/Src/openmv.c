#include "stm32f10x.h"                  // Device header
#include "openmv.h"
_User_USART openmv;
//PA9->p5 PA10->p4         
void openmv_receive(int16_t Com_Data)
{
	static uint8_t RxState=0;
	static uint8_t RxCount=0;
	int i ;
	if(RxState == 0 && Com_Data == 0x2c)//����״̬Ϊ0��֡ͷΪ0x2c��0x12����� 
	{
		RxState=1;
		openmv.RxBuffer[RxCount++]=0x2c;
		
	}
	
	else if(RxState == 1 && Com_Data ==0x12)
	{
		RxState=2;
		openmv.RxBuffer[RxCount++]=0x12;
	}
	
	else if(RxState == 2)
	{
		openmv.RxBuffer[RxCount++]=Com_Data;
		if(RxCount >= 10 || Com_Data == 0x5B)
		{
			RxState=3;
			openmv.X = openmv.RxBuffer[RxCount-5];
			openmv.Y = openmv.RxBuffer[RxCount-4];
			openmv.W = openmv.RxBuffer[RxCount-3];
			openmv.H = openmv.RxBuffer[RxCount-2];
			
		}
	}
		else if(RxState==3)//���ս�����־
		{
			if(openmv.RxBuffer[RxCount-1] == 0x5B)
			{
				RxState= 0;
				RxCount= 0;
			}
			else //�쳣״̬
			{
				RxState= 0;
				RxCount= 0;
				for(i=0;i<10;i++)
				{
					openmv.RxBuffer[i]=0x00;
				}	
			}
		}	
		else//����״̬�쳣
			{
				RxState= 0;
				RxCount= 0;
				for(i=0;i<10;i++)
				{
					openmv.RxBuffer[i]=0x00;
				}	
			}
		
}	

void USART1_IRQHandler(void)//�����жϺ������ڽ��մ�openmv���ܵ������� 
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		
		Serial_RxData= USART_ReceiveData(USART1);//��������Ϊ����1 
		openmv_receive(Serial_RxData);//���ܷ����������ݰ� 
		Serial_RxFlag = 1;//��־λ��1 
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//�����־ 
	}
} 

