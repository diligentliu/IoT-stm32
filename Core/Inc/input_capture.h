#ifndef STM32_STD_INPUT_CAPTURE_H
#define STM32_STD_INPUT_CAPTURE_H

#include "main.h"

void ic_init();
uint32_t ic_get_freq();
uint32_t ic_get_duty();

#endif //STM32_STD_INPUT_CAPTURE_H
