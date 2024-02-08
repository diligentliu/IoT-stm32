#ifndef STM32_STD_DHT11_H
#define STM32_STD_DHT11_H

#include "main.h"

#define DHT11_GPIO_PORT GPIOA
#define DHT11_GPIO_PIN  GPIO_Pin_8

/**
	OLED_Init();
	dht11_init();
	int8_t temp, htmi;
	while (1) {
		dht11_read_data(&temp, &htmi);
		OLED_ShowSignedNum(1, 1, temp, 8);
		OLED_ShowSignedNum(2, 1, htmi, 8);
	}
 */
uint8_t dht11_init();
void dht11_out(uint8_t bit);
uint8_t dht11_in();
void dht11_reset();
uint8_t dht11_check();
uint8_t dht11_read_bit();
uint8_t dht11_read_byte();
uint8_t dht11_read_data(uint8_t *temp1, uint8_t *temp2, uint8_t *htmi1, uint8_t *htmi2);

#endif //STM32_STD_DHT11_H
