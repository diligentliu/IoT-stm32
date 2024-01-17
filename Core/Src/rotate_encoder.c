#include "rotate_encoder.h"

int16_t encoder_count = 0;

void rotate_encoder_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IPU;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInitTypeDef);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

	EXTI_InitTypeDef extiInitTypeDef;
	extiInitTypeDef.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	extiInitTypeDef.EXTI_LineCmd = ENABLE;
	extiInitTypeDef.EXTI_Mode = EXTI_Mode_Interrupt;
	extiInitTypeDef.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&extiInitTypeDef);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef nvicInitTypeDef;
	nvicInitTypeDef.NVIC_IRQChannel = EXTI0_IRQn;
	nvicInitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	nvicInitTypeDef.NVIC_IRQChannelSubPriority = 1;
	nvicInitTypeDef.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init(&nvicInitTypeDef);

	nvicInitTypeDef.NVIC_IRQChannel = EXTI1_IRQn;
	nvicInitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	nvicInitTypeDef.NVIC_IRQChannelSubPriority = 1;
	nvicInitTypeDef.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Init(&nvicInitTypeDef);
}

int16_t get_encoder() {
	int16_t temp = encoder_count;
	encoder_count = 0;
	return temp;
}

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) == SET) {
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
			encoder_count--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line1) == SET) {
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) {
			encoder_count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
