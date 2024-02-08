#include "dht11.h"

uint8_t dht11_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInitTypeDef.GPIO_Pin = DHT11_GPIO_PIN;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_GPIO_PORT, &gpioInitTypeDef);

	dht11_reset();
	return dht11_check();
}

void dht11_out(uint8_t bit) {
	GPIO_WriteBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN, (BitAction) bit);
}

uint8_t dht11_in() {
	return GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
}

void dht11_reset() {
	dht11_out(0);
	delay_ms(20);
	dht11_out(1);
	delay_us(30);
}

/**
 * 检查 DHT11 模块是否响应
 * @return 如果响应返回 0, 否则为非零
 */
uint8_t dht11_check() {
	uint8_t retry = 0;
	uint8_t rval = 0;

	while (dht11_in() && retry < 100) {
		++retry;
		delay_us(1);
	}
	if (retry >= 100) {
		rval = 1;
	} else {
		retry = 0;
		while (!dht11_in() && retry < 100) {
			++retry;
			delay_us(1);
		}
		if (retry >= 100) {
			return 1;
		}
	}
	return rval;
}

uint8_t dht11_read_bit() {
	uint8_t retry = 0;
	while (dht11_in());
	while (!dht11_in());
	delay_us(40);
	return dht11_in();
}

uint8_t dht11_read_byte() {
	uint8_t data = 0;
	for (uint8_t i = 0; i < 8; ++i) {
		data <<= 1;
		data |= dht11_read_bit();
	}
	return data;
}

uint8_t dht11_read_data(uint8_t *temp1, uint8_t *temp2, uint8_t *htmi1, uint8_t *htmi2) {
	uint8_t buf[5];
	dht11_reset();
	if (!dht11_check()) {
		for (uint8_t i = 0; i < 5; ++i) {
			buf[i] = dht11_read_byte();
		}
		if (buf[0] + buf[1] + buf[2] + buf[3] == buf[4]) {
			*htmi1 = buf[0];
			*htmi2 = buf[1];
			*temp1 = buf[2];
			*temp2 = buf[3];
			return 0;
		}
	}
	return 1;
}