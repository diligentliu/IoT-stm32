#include "my_usart2.h"

uint16_t USART2_RxCounter = 0;
char USART2_RxBuff[1024];

void My_USART2(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART2_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = USART2_GPIO_PIN_TX;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = USART2_GPIO_PIN_RX;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	USART2_InitStruct.USART_BaudRate = 115200;
	USART2_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART2_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART2_InitStruct.USART_Parity = USART_Parity_No;
	USART2_InitStruct.USART_StopBits = USART_StopBits_1;
	USART2_InitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2, &USART2_InitStruct);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

__aligned(8) char USART2_TxBuff[256];

void u2_printf(char *fmt, ...) {
	unsigned int i = 0, length = 0;

	va_list ap;
	va_start(ap, fmt);
	vsprintf(USART2_TxBuff, fmt, ap);
	va_end(ap);

	length = strlen((const char *) USART2_TxBuff);
	while (i < length) {
		USART_SendByte(USART2, USART2_TxBuff[i]);
		i++;
	}
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

extern int8_t connect_flag;
void USART2_IRQHandler() {
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		if (connect_flag == 0) {
			char c = USART_ReceiveData(USART2);
			if (c) {
				USART2_RxBuff[USART2_RxCounter++] = c;
			}
		} else {
			USART2_RxBuff[USART2_RxCounter] = USART_ReceiveData(USART2);
			if (USART2_RxCounter == 0) {
				TIM_Cmd(TIM4, ENABLE);
			} else {
				TIM_SetCounter(TIM4, 0);
			}
			++USART2_RxCounter;
		}
	}
}

void u2_TxData(unsigned char *data) {
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	int size = data[0] * 256 + data[1] + 2;
	for (int i = 2; i < size; i++) {
		// u1_printf("%02x ", data[i]);
		USART_SendData(USART2, data[i]);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	}
}