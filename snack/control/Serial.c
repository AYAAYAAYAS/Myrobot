#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
uint8_t Serial_RxData;
uint8_t Serial_RxFlag;
uint8_t res;
void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}

//void USART3_Init(u32 baud)   
//{  
//    USART_InitTypeDef USART_InitStructure;  
//    NVIC_InitTypeDef NVIC_InitStructure;   
//    GPIO_InitTypeDef GPIO_InitStructure;    //声明一个结构体变量，用来初始化GPIO  
//    //使能串口的RCC时钟  
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //使能UART3所在GPIOB的时钟  
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
// 
//    //串口使用的GPIO口配置  
//    // Configure USART3 Tx (PB.10) as alternate function push-pull  
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
//    GPIO_Init(GPIOB, &GPIO_InitStructure); 
// 
//    // Configure USART3 Rx (PB.11) as input floating    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
//    GPIO_Init(GPIOB, &GPIO_InitStructure);   
// 
//    //串口中断配置  
//    //Configure the NVIC Preemption Priority Bits     
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
// 
//    // Enable the USART3 Interrupt   
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级3
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
//    NVIC_Init(&NVIC_InitStructure);  
// 
//    //配置串口  
//    USART_InitStructure.USART_BaudRate = baud;  
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
//    USART_InitStructure.USART_Parity = USART_Parity_No;  
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
// 
//    // Configure USART3   
//    USART_Init(USART3, &USART_InitStructure);//配置串口3 
//    // Enable USART3 Receive interrupts 使能串口接收中断  
//    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  
//    // Enable the USART3   
//    USART_Cmd(USART3, ENABLE);//使能串口3       
//      
//}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}
/********************************************/
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

/*void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//标志位收取
	{
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}*/
//void UART3_IRQHandler(void)  
//{  
//    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)  
// {  
//	USART_ClearFlag(USART3, USART_FLAG_RXNE);
//     res= USART_ReceiveData(USART3); 	 
//     USART_SendData(USART3,res);     
//  }  
//}
