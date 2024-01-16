#include "main.h"

uint16_t num = 0;

int main(void) {
	OLED_Init();
	ad_init();

	OLED_ShowString(1, 1, "ADValue:");

	while (1) {
		OLED_ShowNum(1, 9, ad_get_value(), 5);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
