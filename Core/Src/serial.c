#include "serial.h"

void serial_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_9;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_10;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &gpioInitTypeDef);

	USART_InitTypeDef usartInitTypeDef;
	usartInitTypeDef.USART_BaudRate = 9600;
	usartInitTypeDef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInitTypeDef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usartInitTypeDef.USART_Parity = USART_Parity_No;
	usartInitTypeDef.USART_StopBits = USART_StopBits_1;
	usartInitTypeDef.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usartInitTypeDef);

	USART_Cmd(USART1, ENABLE);
}

void serial_send_byte(uint8_t byte) {
	USART_SendData(USART1, byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void serial_send_array(uint8_t *array, uint16_t length) {
	for (int i = 0; i < length; ++i) {
		serial_send_byte(array[i]);
	}
}

void serial_send_string(const char *string) {
	for (int i = 0; string[i] != '\0'; ++i) {
		serial_send_byte(string[i]);
	}
}

uint32_t serial_pow(uint32_t a, uint32_t b) {
	uint32_t ans = 1;
	while (b > 0) {
		if (b & 1) {
			b--;
			ans = ans * a;
		}
		a *= a;
		b >>= 1;
	}
	return ans;
}

void serial_send_number(uint32_t number, uint8_t length) {
	for (int i = 0; i < length; ++i) {
		serial_send_byte(number / serial_pow(10, length - i - 1) % 10 + '0');
	}
}

int __io_putchar(int ch) {
	serial_send_byte(ch);
	return ch;
}

int __io_getchar() {
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int) USART_ReceiveData(USART1);
}