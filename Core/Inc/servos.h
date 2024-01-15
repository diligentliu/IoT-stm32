#ifndef STM32_STD_SERVOS_H
#define STM32_STD_SERVOS_H

#include "main.h"

/**
 * OLED_Init();
	servos_init();
	key_init();

	float angle = 30.0f;
	set_servos_angle(angle);
	while (1) {
		uint8_t key = key_get_num();
		if (key == 1) {
			angle += 30.0f;
			if (angle > 180.0f) {
				angle = 0;
			}
		}
		set_servos_angle(angle);
		OLED_ShowNum(1, 7, angle, 3);
	}
 */
void servos_init();
void set_servos_compare(uint16_t compare);
void set_servos_angle(float angle);
void set_servos_prescaler(uint16_t prescaler);

#endif //STM32_STD_SERVOS_H
