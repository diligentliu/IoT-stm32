#include "spi_hardware.h"

void spi_hardware_w_ss(uint8_t value) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction) value);
}

void spi_hardware_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_4;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IPU;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	SPI_InitTypeDef spiInitTypeDef;
	spiInitTypeDef.SPI_Mode = SPI_Mode_Master;
	spiInitTypeDef.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spiInitTypeDef.SPI_DataSize = SPI_DataSize_8b;
	spiInitTypeDef.SPI_FirstBit = SPI_FirstBit_MSB;
	spiInitTypeDef.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	spiInitTypeDef.SPI_CPOL = SPI_CPOL_Low;
	spiInitTypeDef.SPI_CPHA = SPI_CPHA_1Edge;
	spiInitTypeDef.SPI_NSS = SPI_NSS_Soft;
	spiInitTypeDef.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &spiInitTypeDef);

	SPI_Cmd(SPI1, ENABLE);

	spi_hardware_w_ss(1);
}

void spi_hardware_strat() {
	spi_hardware_w_ss(0);
}

void spi_hardware_stop() {
	spi_hardware_w_ss(1);
}

uint8_t spi_hardware_swap_byte(uint8_t byte_send) {
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	SPI_I2S_SendData(SPI1, byte_send);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);
	return SPI_I2S_ReceiveData(SPI1);
}
