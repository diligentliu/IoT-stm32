#include "wifi.h"

int8_t wifi_config0(int delay) {
	memset(WiFi_RX_BUF, 0, sizeof(WiFi_RX_BUF));
	WiFi_RxCounter = 0;
	while (delay--) {
		delay_ms(1000);
		if (strstr(WiFi_RX_BUF, "ready")) {
			break;
		}
		u1_printf("%s", WiFi_RX_BUF);
	}
	return delay > 0 ? 0 : 1;
}

int8_t wifi_config(int delay, char *cmd, char *response) {
	memset(WiFi_RX_BUF, 0, sizeof(WiFi_RX_BUF));
	WiFi_RxCounter = 0;
	u2_printf("%s\r\n", cmd);
	while (delay--) {
		delay_ms(1000);
		if (strstr(WiFi_RX_BUF, response)) {
			break;
		}
		u1_printf("%d ", delay);
	}
	u1_printf("%s\r\n", WiFi_RX_BUF);
	return delay > 0 ? 0 : 1;
}

int8_t wifi_connect_router(uint8_t delay) {
	memset(WiFi_RX_BUF, 0, sizeof(WiFi_RX_BUF));
	WiFi_RxCounter = 0;
	u2_printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
	while (delay--) {
		delay_ms(1000);
		if (strstr(WiFi_RX_BUF, "OK")) {
			break;
		}
		u1_printf("%d ", delay);
	}
	u1_printf("%s\r\n", WiFi_RX_BUF);
	return delay > 0 ? 0 : 1;
}

int8_t wifi_tcp_connect(const char *server_ip, const int server_port, int delay) {
	memset(WiFi_RX_BUF, 0, sizeof(WiFi_RX_BUF));
	WiFi_RxCounter = 0;
	u2_printf("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", server_ip, server_port);
	while (delay--) {
		delay_ms(1000);
		if (strstr(WiFi_RX_BUF, "OK")) {
			break;
		}
		u1_printf("%d ", delay);
	}
	u1_printf("%s\r\n", WiFi_RX_BUF);
	return delay > 0 ? 0 : 1;
}

int8_t wifi_connect(const char *server_ip, const int server_port) {
	// 0. 复位
	u1_printf("0、准备复位!\r\n");
	if (wifi_config0(500)) {
		u1_printf("复位失败!\r\n");
		return -1;
	} else {
		u1_printf("复位成功!\r\n");
	}
	// 1. 配置WIFI模式
	u1_printf("1、准备配置WIFI模式!\r\n");
	if (wifi_config(50, "AT+CWMODE=1\r\n", "OK")) {
		u1_printf("配置WIFI模式失败!\r\n");
		return -1;
	} else {
		u1_printf("配置WIFI模式成功!\r\n");
	}
	u1_printf("\r\n");
	// 2. 重启(命令方式)
	u1_printf("2、准备复位!\r\n");
	if (wifi_config(100, "AT+RST\r\n", "ready")) {
		u1_printf("复位失败!\r\n");
		return -1;
	} else {
		u1_printf("复位成功!\r\n");
	}
	u1_printf("\r\n");
	// 3. 取消自动连接
	u1_printf("3、准备取消自动连接\r\n");
	if (wifi_config(50, "AT+CWAUTOCONN=0\r\n", "OK")) {
		u1_printf("取消自动连接失败!\r\n");
		return -1;
	} else {
		u1_printf("取消自动连接成功!\r\n");
	}
	u1_printf("\r\n");
	// 4. 连接路由器
	u1_printf("4、准备连接路由器\r\n");
	if (wifi_connect_router(50)) {
		u1_printf("连接路由器失败!\r\n");
		return -1;
	} else {
		u1_printf("连接路由器成功!\r\n");
	}
	u1_printf("\r\n");
	// 5. 配置单路连接模式
	u1_printf("5、准备配置单路连接模式!\r\n");
	if (wifi_config(50, "AT+CIPMUX=0\r\n", "OK")) {
		u1_printf("配置单路连接模式失败!\r\n");
		return -1;
	} else {
		u1_printf("配置单路连接模式成功!\r\n");
	}
	u1_printf("\r\n");
	// 6. 开启透传模式
	u1_printf("6、准备开启透传模式\r\n");
	if (wifi_config(50, "AT+CIPMODE=1\r\n", "OK")) {
		u1_printf("开启透传模式失败!\r\n");
		return -1;
	} else {
		u1_printf("开启透传模式成功!\r\n");
	}
	u1_printf("\r\n");
	// 7. 建立TCP连接
	u1_printf("7、准备建立TCP连接\r\n");
	if (wifi_tcp_connect(server_ip, server_port, 50)) {
		u1_printf("建立TCP连接失败!\r\n");
		return -1;
	} else {
		u1_printf("建立TCP连接成功!\r\n");
	}
	u1_printf("\r\n");
	// 8、进入透传模式
	u1_printf("8、准备进入透传模式\r\n");
	if (wifi_config(50, "AT+CIPSEND\r\n", "\r\nOK\r\n\r\n>")) {
		u1_printf("进入透传模式失败!\r\n");
		return -1;
	} else {
		u1_printf("进入透传模式成功!\r\n");
	}
	return 0;
}
