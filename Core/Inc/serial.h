#ifndef STM32_STD_SERIAL_H
#define STM32_STD_SERIAL_H

#include <stdio.h>
#include "main.h"

/**
	OLED_Init();
	serial_init();
	serial_send_byte(0x41);

	uint8_t array[8];
	for (int i = 0; i < 8; ++i) {
		array[i] = 'a' + i;
	}
	serial_send_array(array, 8);
	const char *string = "我可以是中文嘛？";
	serial_send_string(string);
	serial_send_number(9999, 4);

	printf("Num = %d\r\n", 666);

	while (1) {
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
			uint8_t data = USART_ReceiveData(USART1);
			OLED_ShowHexNum(1, 1, data, 2);
		}
	}
 */
void serial_init();
void serial_send_byte(uint8_t byte);
void serial_send_array(uint8_t *array, uint16_t length);
void serial_send_string(const char *string);
void serial_send_number(uint32_t number, uint8_t length);
int serial_read_byte();

#endif //STM32_STD_SERIAL_H
