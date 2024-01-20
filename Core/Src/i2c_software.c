#include "i2c_software.h"

void i2c_w_scl(uint8_t val) {
	GPIO_WriteBit(SCL_PORT, SCL_PIN, (BitAction) val);
	delay_us(10);
}

void i2c_w_sda(uint8_t val) {
	GPIO_WriteBit(SDA_PORT, SDA_PIN, (BitAction) val);
	delay_us(10);
}

uint8_t i2c_r_sda() {
	uint8_t val = GPIO_ReadInputDataBit(SDA_PORT, SDA_PIN);
	delay_us(10);
	return val;
}

void i2c_software_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInitTypeDef.GPIO_Pin = SCL_PIN | SDA_PIN;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCL_PORT, &gpioInitTypeDef);

	GPIO_SetBits(SCL_PORT, SCL_PIN | SDA_PIN);
}

void i2c_software_start() {
	i2c_w_sda(1);
	i2c_w_scl(1);
	i2c_w_sda(0);
	i2c_w_scl(0);
}

void i2c_software_stop() {
	i2c_w_sda(0);
	i2c_w_scl(1);
	i2c_w_sda(1);
}

void i2c_software_send_byte(uint8_t byte) {
	for (int i = 7; i >= 0; --i) {
		i2c_w_sda(byte & (1 << i));
		i2c_w_scl(1);
		i2c_w_scl(0);
	}
}

uint8_t i2c_software_receive_byte() {
	uint8_t val = 0;
	i2c_w_sda(1);
	for (int i = 7; i >= 0; --i) {
		i2c_w_scl(1);
		val |= (i2c_r_sda() << i);
		i2c_w_scl(0);
	}
	return val;
}

void i2c_software_send_ack(uint8_t byte) {
	i2c_w_sda(byte);
	i2c_w_scl(1);
	i2c_w_scl(0);
}

uint8_t i2c_software_receive_ack() {
	i2c_w_sda(1);
	i2c_w_scl(1);
	uint8_t val = i2c_r_sda();
	i2c_w_scl(0);
	return val;
}