#include "input_capture.h"

void ic_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_InternalClockConfig(TIM3);

	TIM_TimeBaseInitTypeDef timTimeBaseInitTypeDef;
	timTimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
	timTimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
	timTimeBaseInitTypeDef.TIM_Period = 65536 - 1;
	timTimeBaseInitTypeDef.TIM_Prescaler = 72 - 1;
	timTimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timTimeBaseInitTypeDef);

	TIM_ICInitTypeDef timIcInitTypeDef;
	timIcInitTypeDef.TIM_Channel = TIM_Channel_1;
	timIcInitTypeDef.TIM_ICFilter = 0xF;
	timIcInitTypeDef.TIM_ICPolarity = TIM_ICPolarity_Rising;
	timIcInitTypeDef.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	timIcInitTypeDef.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(TIM3, &timIcInitTypeDef);

	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

	TIM_Cmd(TIM3, ENABLE);
}

uint32_t ic_get_freq() {
	return (72000000 / TIM_GetPrescaler(TIM3)) / TIM_GetCapture1(TIM3);
}

uint32_t ic_get_duty() {
	return TIM_GetCapture2(TIM3) * 100 / TIM_GetCapture1(TIM3);
}