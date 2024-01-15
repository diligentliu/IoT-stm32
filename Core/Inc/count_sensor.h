#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H

#include "stm32f10x_it.h"

void count_sensor_init(void);
uint16_t get_count_sensor(void);

#endif
