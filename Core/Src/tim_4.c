#include "tim_4.h"

void TIM4_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_Cmd(TIM4, DISABLE);
}

void TIM4_IRQHandler() {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		mqtt_rx_in_ptr[0] = USART2_RxCounter / 256;
		mqtt_rx_in_ptr[1] = USART2_RxCounter % 256;
		memcpy(&mqtt_rx_in_ptr[2], USART2_RxBuff, USART2_RxCounter);
		mqtt_rx_in_ptr += 400;
		if (mqtt_rx_in_ptr == mqtt_rx_end_ptr) {
			mqtt_rx_in_ptr = mqtt_rx_buff[0];
		}
		USART2_RxCounter = 0;
		TIM_Cmd(TIM4, DISABLE);
		TIM_SetCounter(TIM4, 0);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}