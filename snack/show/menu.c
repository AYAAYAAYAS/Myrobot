#include "stm32f10x.h"                  // Device header
#include "menu_key.h"
#include "OLED.h"
//#include "openmv.h"
#include "Serial.h"
//extern uint8_t Serial_RxData;
//extern uint8_t Serial_RxFlag;
//extern _User_USART openmv;

uint8_t menu()
{
                   
	uint8_t menu_scan=1;
	uint8_t menu_flag;
	
	OLED_Init();
		OLED_ShowString(1,2,"*");
		OLED_ShowString(2,2," ");
		OLED_ShowString(3,2," ");
		OLED_ShowString(1,4,"PID");
		OLED_ShowString(2,4,"axis");
		OLED_ShowString(3,4,"action");
		menu_key_Init();
	while(1)
	{
		menu_flag=key_read();
		if(menu_flag==1)
		{
			menu_scan++;
			if(menu_scan==4)
			{
				menu_scan=1;
			}
		}	
		else if(menu_flag==2)
		{
			OLED_Clear();
			return(menu_scan);
		}
		switch(menu_scan)//¹â±ê
		{
			case 1: 
			{
				OLED_ShowString(1,2,"*");
				OLED_ShowString(2,2," ");
				OLED_ShowString(3,2," ");
			}break;
			case 2:
			{
				OLED_ShowString(1,2," ");
				OLED_ShowString(2,2,"*");
				OLED_ShowString(3,2," ");
			}break;
			case 3:
			{
				OLED_ShowString(1,2," ");
				OLED_ShowString(2,2," ");
				OLED_ShowString(3,2,"*");
				
			}break;
		}
	}
}

//int axis()
//{
//		OLED_ShowString(1,2,"X:");
//		OLED_ShowString(2,2,"Y:");
//		OLED_ShowString(3,2,"W:");
//		OLED_ShowString(4,2,"H:");
//	while(1)
//	{
//		openmv_receive(Serial_RxData);
//		OLED_ShowNum(1,4,openmv.X, 3);
//		OLED_ShowNum(2,4,openmv.Y, 3);
//		OLED_ShowNum(3,4,openmv.W, 3);
//		OLED_ShowNum(4,4,openmv.H, 3);
//		if(key_read()==3)
//		{
//			break;
//		}
//	}
//		return 0;
//}


//void USART1_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		
//		Serial_RxData= USART_ReceiveData(USART1);
//		openmv_receive(Serial_RxData);
//		Serial_RxFlag = 1;
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}
// 