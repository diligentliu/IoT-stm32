#include "main.h"

uint16_t num = 0;

int main(void) {
	OLED_Init();

	while (1) {

	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
