#include "timer.h"

void timer_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitTypeDef timTimeBaseInitTypeDef;
	timTimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
	timTimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
	timTimeBaseInitTypeDef.TIM_Period = 10000 - 1;
	timTimeBaseInitTypeDef.TIM_Prescaler = 7200 - 1;
	timTimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timTimeBaseInitTypeDef);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef nvicInitTypeDef;
	nvicInitTypeDef.NVIC_IRQChannel = TIM2_IRQn;
	nvicInitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	nvicInitTypeDef.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInitTypeDef.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvicInitTypeDef);

	TIM_Cmd(TIM2, ENABLE);
}
