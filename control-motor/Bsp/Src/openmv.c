#include "openmv.h"
#include "OLED.h"
//PA9->p5 PA10->p4     
uint8_t Cx=0,Cy=0,Cw=0,Ch=0;
void openmv_receive(int16_t Com_Data)
{
	static uint8_t RxState=0;
	static uint8_t RxCount=0;
	static uint8_t RxBuffer[count]={0};			//���ջ���	
	int i ;
	if(RxState == 0 && Com_Data == 0x2C)//����״̬Ϊ0��֡ͷΪ0x2c��0x12����� 
	{
		RxState=1;
		RxBuffer[RxCount++]=0x2C;
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
	}
	
	else if(RxState == 1 && Com_Data ==0x12)
	{
		RxState=2;
		RxBuffer[RxCount++]=0x12;
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
	}
	
	else if(RxState == 2)
	{
		RxBuffer[RxCount++]=Com_Data;
		if(RxCount >= 10 || Com_Data == 0x5B)
		{
			RxState=3;
			Cx= RxBuffer[RxCount-7];
			Cy= RxBuffer[RxCount-6];
			Cw= RxBuffer[RxCount-5];
			Ch= RxBuffer[RxCount-4];

			
		}
	}
		else if(RxState==3)//���ս�����־
		{
			if(RxBuffer[RxCount-1] == 0x5B)
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
					RxBuffer[i]=0x00;
				}	
			}
		}	
		else//����״̬�쳣
			{
				RxState= 0;
				RxCount= 0;
				for(i=0;i<10;i++)
				{
					RxBuffer[i]=0x00;
				}	
			}
		
}	



//void USART1_IRQHandler(void)//�����жϺ������ڽ��մ�openmv���ܵ������� 
//{
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		
//		Serial_RxData= USART_ReceiveData(USART1);//��������Ϊ����1 
//		openmv_receive(Serial_RxData);//���ܷ����������ݰ� 
//		Serial_RxFlag = 1;//��־λ��1 
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//�����־ 
//	}
//} 

