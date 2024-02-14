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

int wifi_connect(const char* server_ip, const uint16_t server_port) {
	wifi_config("AT+RST", "ready",
	            "RESET", 10);
	wifi_config("AT+CWMODE=1", "OK",
				"WiFi Mode", 10);
	wifi_config("AT+RST", "ready",
				"RESET", 10);
	wifi_config("AT+CWAUTOCONN=0", "OK", "Cancel automatic connection", 10);
	wifi_connect_router(10);
	wifi_config("AT+CIPMUX=0", "OK",
				"Single connection mode", 10);
	wifi_config("AT+CIPMODE=1", "OK",
				"SerialNet mode", 10);
	char command[1024];
	sprintf(command, "AT+CIPSTART=\"TCP\",\"%s\",%d", server_ip, server_port);
	wifi_config(command, "OK",
				"TCP connection", 10);
	wifi_config("AT+CIPSEND", "OK",
				"Enter SerialNet mode", 10);
}