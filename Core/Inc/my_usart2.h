#ifndef __MY_USART2_H__
#define __MY_USART2_H__

#include "main.h"

#define USART2_GPIO_PIN_TX   GPIO_Pin_2
#define USART2_GPIO_PIN_RX   GPIO_Pin_3

extern uint16_t USART2_RxCounter;
extern char USART2_RxBuff[1024];

void My_USART2(void);
void USART_SendByte(USART_TypeDef *USARTx, uint16_t Data);
void u2_printf(char *fmt, ...);
void u2_TxData(unsigned char *data);

#endif

