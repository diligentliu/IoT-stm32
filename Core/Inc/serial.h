#ifndef STM32_STD_SERIAL_H
#define STM32_STD_SERIAL_H

#include <stdio.h>
#include "main.h"

void serial_init();
void serial_send_byte(uint8_t byte);
void serial_send_array(uint8_t *array, uint16_t length);
void serial_send_string(const char *string);
void serial_send_number(uint32_t number, uint8_t length);

#endif //STM32_STD_SERIAL_H
