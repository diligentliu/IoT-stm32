#ifndef STM32_STD_WIFI_H
#define STM32_STD_WIFI_H

#include "main.h"

#define WiFi_RxCounter  USART2_RxCounter
#define WiFi_RX_BUF     USART2_RxBuff

#define SSID        "CU-B53B"
#define PASSWORD    "a12344321a"

int wifi_config(char *command, char *command_success_flag,
                char *describe, uint8_t delay);
int wifi_connect_router(uint8_t delay);
int wifi_connect(const char* server_ip, const uint16_t server_port);

#endif //STM32_STD_WIFI_H
