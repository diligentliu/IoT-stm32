#ifndef STM32_STD_DHT11_H
#define STM32_STD_DHT11_H

#include "main.h"

#define DHT11_GPIO_PORT GPIOA
#define DHT11_GPIO_PIN  GPIO_Pin_8

/**
	OLED_Init();
	dht11_init();
	while (1) {
		int8_t temp[2], htmi[2];
		dht11_read_data(temp, temp + 1, htmi, htmi + 1);
		OLED_ShowNum(1, 1, temp[0], 2);
		OLED_ShowChar(1, 3, '.');
		OLED_ShowNum(1, 4, temp[1], 1);
		OLED_ShowNum(2, 1, htmi[0], 2);
		OLED_ShowChar(2, 3, '.');
		OLED_ShowNum(2, 4, htmi[1], 1);
	}
 */
uint8_t dht11_init();
void dht11_out(uint8_t bit);
uint8_t dht11_in();
void dht11_reset();
uint8_t dht11_check();
uint8_t dht11_read_bit();
uint8_t dht11_read_byte();
uint8_t dht11_read_data(int8_t *temp1, int8_t *temp2, int8_t *htmi1, int8_t *htmi2);
void Sensor_DHT11(void);

#endif //STM32_STD_DHT11_H
