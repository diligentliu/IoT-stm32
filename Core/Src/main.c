#include "main.h"

uint16_t num = 0;

int main(void) {
	OLED_Init();
	servos_init();
	ic_init();

	OLED_ShowString(1, 1, "Freq : 00000Hz");
	set_servos_prescaler(36 - 1);
	set_servos_compare(50);

	while (1) {
		OLED_ShowNum(1, 8, ic_get_freq(), 5);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
