#ifndef __MY_USART1_H__
#define __MY_USART1_H__

#include "main.h"

#define USART1_GPIO_PIN_TX   GPIO_Pin_9
#define USART1_GPIO_PIN_RX   GPIO_Pin_10


void My_USART1(void);
void u1_printf(char *fmt, ...);

#endif

