#include "spi_software.h"

void spi_software_w_ss(uint8_t value) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction) value);
}

void spi_software_w_sck(uint8_t value) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction) value);
}

void spi_software_w_mosi(uint8_t value) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction) value);
}

uint8_t spi_software_r_miso() {
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void spi_software_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IPU;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	spi_software_w_ss(1);
	spi_software_w_sck(0);
}

void spi_software_strat() {
	spi_software_w_ss(0);
}

void spi_software_stop() {
	spi_software_w_ss(1);
}

uint8_t spi_software_swap_byte(uint8_t byte_send) {
	uint8_t byte_receive = 0x00;

	for (int i = 7; i >= 0; --i) {
		spi_software_w_mosi(byte_send & (1 << i));
		spi_software_w_sck(1);
		byte_receive |= (spi_software_r_miso() << i);
		spi_software_w_sck(0);
	}
	return byte_receive;
}