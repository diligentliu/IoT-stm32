#include "outer_timer.h"

void outer_timer_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_0;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IPD;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);

	TIM_TimeBaseInitTypeDef timTimeBaseInitTypeDef;
	timTimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
	timTimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
	timTimeBaseInitTypeDef.TIM_Period = 10 - 1;
	timTimeBaseInitTypeDef.TIM_Prescaler = 1;
	timTimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timTimeBaseInitTypeDef);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef nvicInitTypeDef;
	nvicInitTypeDef.NVIC_IRQChannel = TIM2_IRQn;
	nvicInitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	nvicInitTypeDef.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInitTypeDef.NVIC_IRQChannelSubPriority = 3;
	OLED_ShowNum(2, 1, 1, 1);
	NVIC_Init(&nvicInitTypeDef);
	OLED_ShowNum(2, 1, 2, 1);

	TIM_Cmd(TIM2, ENABLE);
	OLED_ShowNum(2, 1, 3, 1);
}

uint16_t timer_get_count() {
	return TIM_GetCounter(TIM2);
}
