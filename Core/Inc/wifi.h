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

#define SSID        "CU_my6R"
#define PASSWORD    "LW123321"

int8_t wifi_config(int delay, char *cmd, char *response);
int8_t wifi_connect_router(uint8_t delay);
int8_t wifi_tcp_connect(const char *server_ip, int server_port, int delay);
int8_t wifi_connect(const char *server_ip, int server_port);

#endif //STM32_STD_WIFI_H
