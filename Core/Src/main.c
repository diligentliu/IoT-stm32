#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x04, 0x03, 0x02, 0x01};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	OLED_Init();
	dht11_init();
	int8_t temp, htmi;
	while (1) {
		dht11_read_data(&temp, &htmi);
		OLED_ShowSignedNum(1, 1, temp, 8);
		OLED_ShowSignedNum(2, 1, htmi, 8);
	}
}

void TIM2_IRQHandler() {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
