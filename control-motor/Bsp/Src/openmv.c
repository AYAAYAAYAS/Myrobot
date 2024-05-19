#include "openmv.h"
#include "OLED.h"
//PA9->p5 PA10->p4     
uint8_t buffer_1_i=0,buffer_1_f=0,buffer_2_i=0,buffer_2_f=0,buffer_3=0;
void openmv_receive(int16_t Com_Data)
{
	static uint8_t RxState=0;
	static uint8_t RxCount=0;
	static uint8_t RxBuffer[count]={0};			//接收缓存	
	int i ;
	if(RxState == 0 && Com_Data == 0x2C)//定义状态为0，帧头为0x2c，0x12的情况 
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
		// b',\x12 \x06\x00 $\x00 2\x00 R\x00 \x01\x00 ['
		RxBuffer[RxCount++]=Com_Data;
		if(RxCount >= 10 || Com_Data == 0x5B)
		{
			RxState=3;
			buffer_1_i= RxBuffer[RxCount-8];
		 	buffer_1_f= RxBuffer[RxCount-6];
			buffer_2_i= RxBuffer[RxCount-4];
			buffer_2_f= RxBuffer[RxCount-2];
			buffer_3  =	RxBuffer[RxCount];
			
		}
		//todo 
	}
		else if(RxState==3)//接收结束标志
		{
			if(RxBuffer[RxCount-1] == 0x5B)
			{
				RxState= 0;
				RxCount= 0;
			}
			else //异常状态
			{
				RxState= 0;
				RxCount= 0;
				for(i=0;i<10;i++)
				{
					RxBuffer[i]=0x00;
				}	
			}
		}	
		else//接收状态异常
			{
				RxState= 0;
				RxCount= 0;
				for(i=0;i<10;i++)
				{
					RxBuffer[i]=0x00;
				}	
			}
		
}	



//void USART1_IRQHandler(void)//串口中断函数用于接收从openmv接受到的数据 
//{
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		
//		Serial_RxData= USART_ReceiveData(USART1);//接受数据为串口1 
//		openmv_receive(Serial_RxData);//接受发过来的数据包 
//		Serial_RxFlag = 1;//标志位置1 
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清除标志 
//	}
//} 

