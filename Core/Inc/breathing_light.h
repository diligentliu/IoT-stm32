#ifndef STM32_STD_BREATHING_LIGHT_H
#define STM32_STD_BREATHING_LIGHT_H

#include "main.h"

/**
 * breathing_light_init();
 *
 *	while (1) {
 *		for (uint16_t i = 0; i <= 100; ++i) {
 *			pwm_set_compare(i);
 *			delay_ms(20);
 *		}
 *		for (uint16_t i = 0; i <= 100; ++i) {
 *			pwm_set_compare(100 - i);
 *			delay_ms(20);
 *		}
 *	}
 */
void breathing_light_init();

#endif //STM32_STD_BREATHING_LIGHT_H
