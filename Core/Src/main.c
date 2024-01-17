#include "main.h"

uint16_t num = 0;
uint8_t data_1[] = {0x01, 0x02, 0x03, 0x04};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	OLED_Init();
	dma_data_transfer_init((uint32_t) data_1, (uint32_t) data_2, 4);

	OLED_ShowHexNum(1, 1, data_1[0], 2);
	OLED_ShowHexNum(1, 4, data_1[1], 2);
	OLED_ShowHexNum(1, 7, data_1[2], 2);
	OLED_ShowHexNum(1,10, data_1[3], 2);

	OLED_ShowHexNum(2, 1, data_2[0], 2);
	OLED_ShowHexNum(2, 4, data_2[1], 2);
	OLED_ShowHexNum(2, 7, data_2[2], 2);
	OLED_ShowHexNum(2,10, data_2[3], 2);

	while (1) {
		data_1[0]++;
		data_1[1]++;
		data_1[2]++;
		data_1[3]++;

		OLED_ShowHexNum(1, 1, data_1[0], 2);
		OLED_ShowHexNum(1, 4, data_1[1], 2);
		OLED_ShowHexNum(1, 7, data_1[2], 2);
		OLED_ShowHexNum(1,10, data_1[3], 2);

		OLED_ShowHexNum(2, 1, data_2[0], 2);
		OLED_ShowHexNum(2, 4, data_2[1], 2);
		OLED_ShowHexNum(2, 7, data_2[2], 2);
		OLED_ShowHexNum(2,10, data_2[3], 2);

		delay_ms(1000);
		dma_data_transfer();
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
