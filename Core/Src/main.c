#include "main.h"

uint16_t num = 0;

int main(void) {
	OLED_Init();
	pwm_init();
	ic_init();

	OLED_ShowString(1, 1, "Freq : 00000Hz");
	OLED_ShowString(2, 1, "Duty : 00%");

	pwm_set_prescaler(720 - 1);
	pwm_set_compare(50);

	while (1) {
		OLED_ShowNum(1, 8, ic_get_freq(), 5);
		OLED_ShowNum(2, 8, ic_get_duty(), 2);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
