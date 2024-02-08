#include "wifi.h"

int wifi_config(char *command, char *command_success_flag,
                char *describe, uint8_t delay) {
	bzero(WiFi_RX_BUF, sizeof(WiFi_RX_BUF));
	WiFi_RxCounter = 0;
	u2_printf("%s\r\n", command);
	while (delay--) {
		delay_s(1);
		if (strstr(WiFi_RX_BUF, command_success_flag)) {
			break;
		}
		u1_printf("=");
	}
	u1_printf("\r\n");
	if (delay > 0) {
		u1_printf("%s SUCCESS\r\n", describe);
		return 0;
	} else {
		u1_printf("%s FAILED\r\n", describe);
		return -1;
	}
}

int wifi_connect_router(uint8_t delay) {
	bzero(WiFi_RX_BUF, sizeof(WiFi_RX_BUF));
	WiFi_RxCounter = 0;
	u2_printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
	while (delay--) {
		delay_s(1);
		if (strstr(WiFi_RX_BUF, "OK")) {
			break;
		}
		u1_printf("=");
	}
	u1_printf("\r\n");
	if (delay > 0) {
		u1_printf("Connect router SUCCESS\r\n");
		return 0;
	} else {
		u1_printf("Connect router FAILED\r\n");
		return -1;
	}
}