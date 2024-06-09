RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructure;
	TIM_TimeBaseInitstructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstructure.TIM_Period=10000-1;  //ARR
	TIM_TimeBaseInitstructure.TIM_Prescaler=7200-1;//PSC
	TIM_TimeBaseInitstructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_FLAG_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=TIM2_IRQn ;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstructure);
	
	TIM_Cmd(TIM2,ENABLE);
