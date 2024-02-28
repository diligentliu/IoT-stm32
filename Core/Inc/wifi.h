#ifndef STM32_STD_WIFI_H
#define STM32_STD_WIFI_H

#include "main.h"
/**
 * 紫色 —— TX
 * 蓝色 —— GND
 * 灰色 —— CH_PD
 * 绿色 —— VCC
 * 白色 —— RX
 */
#define WiFi_RxCounter  USART2_RxCounter
#define WiFi_RX_BUF     USART2_RxBuff

#define SSID        "Diligent iPhone"
#define PASSWORD    "         "

int8_t wifi_config(int8_t delay, char *cmd, char *response);
int8_t wifi_connect_router(int8_t delay);
int8_t wifi_tcp_connect(const char *server_ip, int server_port, int8_t delay);
int8_t wifi_connect(const char *server_ip, int server_port);

#endif //STM32_STD_WIFI_H
