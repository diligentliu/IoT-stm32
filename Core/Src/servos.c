#include "servos.h"

void servos_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseInitTypeDef timTimeBaseInitTypeDef;
	timTimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
	timTimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
	timTimeBaseInitTypeDef.TIM_Period = 20000 - 1;
	timTimeBaseInitTypeDef.TIM_Prescaler = 72 - 1;
	timTimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timTimeBaseInitTypeDef);

	TIM_OCInitTypeDef timOcInitTypeDef;
	TIM_OCStructInit(&timOcInitTypeDef);
	timOcInitTypeDef.TIM_OCMode = TIM_OCMode_PWM1;
	timOcInitTypeDef.TIM_OCPolarity = TIM_OCPolarity_High;
	timOcInitTypeDef.TIM_OutputState = TIM_OutputState_Enable;
	timOcInitTypeDef.TIM_Pulse = 500;          // CCR
	TIM_OC2Init(TIM2, &timOcInitTypeDef);

	TIM_Cmd(TIM2, ENABLE);
}

void set_servos_compare(uint16_t compare) {
	TIM_SetCompare2(TIM2, compare);
}

void set_servos_angle(float angle) {
	set_servos_compare(angle / 180.0f * 2000.0f - 500.0f);
}

void set_servos_prescaler(uint16_t prescaler) {
	TIM_PrescalerConfig(TIM2, prescaler, TIM_PSCReloadMode_Immediate);
}
