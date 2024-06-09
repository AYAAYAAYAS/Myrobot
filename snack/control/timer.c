#include "stm32f10x.h"                  // Device header
//����=freq 72000000 /ARR 100 /PSC 1440==500   1/500=2ms
void Init_TIM1(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM1);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;		//ARR 
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter =0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC4
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1_CH1Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1_CHԤװ�ؼĴ���
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
/**************************************************************************
�������ܣ���TIM2��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Init_TIM2(void)
{
	 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼGPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 1-1; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = 65536-1; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0XF;
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0XF;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, 
  TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
 
  TIM_Cmd(TIM2, ENABLE); 
 }
 
/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Init_TIM4(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼGPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 1-1; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = 65536-1; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_ICInitTypeDef TIM_ICInitstructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0XF;
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0XF;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, 
  TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
 
  TIM_Cmd(TIM4, ENABLE); 
}

 /*void TIM2_IRQHandler()
 {
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)== SET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
 }	 */
 	 