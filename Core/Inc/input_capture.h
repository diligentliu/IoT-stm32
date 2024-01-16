#ifndef STM32_STD_INPUT_CAPTURE_H
#define STM32_STD_INPUT_CAPTURE_H

#include "main.h"

/**
 * Usage Example :
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
 */
void ic_init();
uint32_t ic_get_freq();
uint32_t ic_get_duty();

#endif //STM32_STD_INPUT_CAPTURE_H
