#include "tim_3.h"

void TIM3_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_Cmd(TIM3, DISABLE);
}

void TIM3_IRQHandler() {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		u1_printf("what are you doing?\r\n");
		switch (ping_flag) {
			case 0:
			case 1:
			case 2:
				mqtt_ping_message();
				break;
			case 3:
				TIM3_Init(6000 - 1, 36000 - 1);
				TIM_Cmd(TIM3, ENABLE);
				mqtt_ping_message();
				break;
			case 4:
				connect_flag = 0;
				connect_pack_flag = 0;
				subscribe_flag = 0;
				TIM_Cmd(TIM3, DISABLE);
				break;
			default:
				break;
		}
		++ping_flag;
		u1_printf("%d\r\n", mqtt_tx_out_ptr != mqtt_tx_in_ptr);
		int size = mqtt_tx_out_ptr[0] * 256 + mqtt_tx_out_ptr[1] + 2;
		for (int i = 0; i < size; ++i) {
			u1_printf("%02x ", mqtt_tx_out_ptr[i]);
		}
		u1_printf("\r\n");
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}