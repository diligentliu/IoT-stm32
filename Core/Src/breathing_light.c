#include "breathing_light.h"

void breathing_light_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA, GPIO_Pin_0);

	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitTypeDef timTimeBaseInitTypeDef;
	timTimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
	timTimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
	timTimeBaseInitTypeDef.TIM_Prescaler = 300 - 1;
	timTimeBaseInitTypeDef.TIM_Period = 720 - 1;
	timTimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timTimeBaseInitTypeDef);

	TIM_OCInitTypeDef timOcInitTypeDef;
	TIM_OCStructInit(&timOcInitTypeDef);
	timOcInitTypeDef.TIM_OCMode = TIM_OCMode_PWM1;
	timOcInitTypeDef.TIM_OCPolarity = TIM_OCPolarity_High;
	timOcInitTypeDef.TIM_OutputState = TIM_OutputState_Enable;
	timOcInitTypeDef.TIM_Pulse = 50;          // CCR
	TIM_OC1Init(TIM2, &timOcInitTypeDef);

	TIM_Cmd(TIM2, ENABLE);
}

void pwm_set_compare(uint16_t compare) {
	TIM_SetCompare1(TIM2, compare);
}