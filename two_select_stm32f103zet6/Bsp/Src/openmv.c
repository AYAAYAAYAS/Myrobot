#include "openmv.h"
#include "OLED.h"
//PA9->p5 PA10->p4     
uint8_t buffer_1_i=0,buffer_1_f=0,buffer_2_i=0,buffer_2_f=0,buffer_3=0;
float theta_err,rho_err;
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
	}
	
	else if(RxState == 1 && Com_Data ==0x12)
	{
		RxState=2;
		RxBuffer[RxCount++]=0x12;
	}
	
	else if(RxState == 2)
	{
		// b',\x12x\x00\x00\x000\x00\x00\x00['
			//	12.0909
			//	Turn Angle: 48.538284
			//	0.987492

		RxBuffer[RxCount++]=Com_Data;
		if(RxCount >= 10 || Com_Data == 0x5B)
		{
			RxState=3;
			
			buffer_1_i=RxBuffer[2];
			theta_err=buffer_1_i/10+buffer_1_i%10/10;
			rho_err=RxBuffer[6];
			
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

void data_deal(uint8_t *data)
{
	uint8_t theta_org,rho_org;
//	theta_org = (int)(*(data+2)<<0) | (int)(*(data+3)<<8) | (int)(*(data+4)<<16) | (int)(*(data+5)<<24);
//	theta_err = theta_org/100 + 	(theta_org%100)/100 ;

	
}


//void data_deal(uint8_t *data)
//{
////b',\x12\x1e\x04\x00\x00\xeb\x01\x00\x00['
////10.5455 //1054 ->hex 41e
////Turn Angle: 49.177079 //491 ->hex 1eb

//	uint8_t theta_org,rho_org;
//	theta_org = (int)(*(data+2)<<0) | (int)(*(data+3)<<8) | (int)(*(data+4)<<16) | (int)(*(data+5)<<24);
//	theta_err = theta_org/100 + 	(theta_org%100)/100 ;
//	
//	rho_org = (int)(*(data+6)<<0) | (int)(*(data+7)<<8) | (int)(*(data+8)<<16) | (int)(*(data+9)<<24);	
//	rho_err = rho_org/100 + 	(rho_org%10)/100 ;	
//}

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

