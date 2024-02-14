#ifndef STM32_STD_PWM_H
#define STM32_STD_PWM_H

#include "main.h"

void pwm_init();
void pwm_set_compare(uint16_t);
void pwm_set_prescaler(uint16_t prescaler);

#endif //STM32_STD_PWM_H
