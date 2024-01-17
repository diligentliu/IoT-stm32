#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x01, 0x02, 0x03, 0x04};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	OLED_Init();
	rotate_encoder_init();

	while (1) {
		num += get_encoder();
		OLED_ShowSignedNum(1, 1, num, 5);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
