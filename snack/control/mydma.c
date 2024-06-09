#include "stm32f10x.h"                  // Device header

uint16_t ReceiveBuffer[10];

void cmd_Init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitTypeDef DMA_InitStructure;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ReceiveBuffer;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 10;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel5, ENABLE);
	

}
void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel5, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, 10);
	DMA_Cmd(DMA1_Channel5, ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC5);
}


//void DMA1_Channel4_IRQHandler(void)
//{
//	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)==SET)
//	{
//		
//		DMA_ClearFlag(DMA1_FLAG_TC4);
//	}	
//	
//}	