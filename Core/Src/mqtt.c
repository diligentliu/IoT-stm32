#include "mqtt.h"

uint8_t mqtt_buff[400];
char clientId[128];
uint16_t clientId_size;
char username[128];
uint16_t username_size;
char password[128];
uint16_t password_size;

// 发送缓冲区
u_char mqtt_tx_buff[7][400];
u_char *mqtt_tx_in_ptr = mqtt_tx_buff[0];
u_char *mqtt_tx_out_ptr = mqtt_tx_buff[0];
u_char *mqtt_tx_end_ptr = mqtt_tx_buff[6];

uint8_t connect_flag = 0;
uint8_t connect_pack_flag = 0;
uint8_t subscribe_flag = 0;
uint8_t ping_flag = 0;

u_char mqtt_rx_buff[7][400];
u_char *mqtt_rx_in_ptr = mqtt_rx_buff[0];
u_char *mqtt_rx_out_ptr = mqtt_rx_buff[0];
u_char *mqtt_rx_end_ptr = mqtt_rx_buff[6];

void mqtt_data_init() {
	char temp[128];
	memset(clientId, 0, sizeof(clientId));
	sprintf(clientId, "%s|securemode=3,signmethod=hmacsha1|", DEVICE_NAME);
	clientId_size = strlen(clientId);

	memset(username, 0, sizeof(username));
	sprintf(username, "%s&%s", DEVICE_NAME, PRODUCT_KEY);
	username_size = strlen(username);

	memset(temp, 0, sizeof(temp));
	sprintf(temp, "clientId%sdeviceName%sproductKey%s", DEVICE_NAME, DEVICE_NAME, PRODUCT_KEY);
	utils_hmac_sha1(temp, strlen(temp), password, DEVICE_SECRET, DEVICE_SECRET_LEN);
	password_size = strlen(password);
}

void mqtt_flag_re_init() {
	connect_flag = 0;
	connect_pack_flag = 0;
	subscribe_flag = 0;
	ping_flag = 0;
}

void mqtt_connect_message() {
	bzero(mqtt_buff, sizeof(mqtt_buff));
	uint8_t mqtt_buff_index = 0;
	mqtt_buff[mqtt_buff_index++] = 0x10;

	// 有效载荷初始长度
	uint16_t payload_len = clientId_size + 2
	                       + username_size + 2
	                       + password_size + 2;
	// 可变报头
	uint8_t var_header[10] = {
			0x00, 0x04,                     /* length */
			0x4d, 0x51, 0x54, 0x54, /* MQTT */
			0x04,                               /* 协议版本 3.1.1 */
			0xc2, 0x00, 0x64            /* 连接标志 */
	};

	// 剩余长度
	uint8_t remain_size = sizeof(var_header) + payload_len;

	while (remain_size > 0) {
		int len = remain_size % 128;
		remain_size /= 128;
		if (remain_size) {
			len |= 0x80;
		}
		mqtt_buff[mqtt_buff_index++] = len;
	}

	memcpy(mqtt_buff + mqtt_buff_index, var_header, sizeof(var_header));
	mqtt_buff_index += sizeof(var_header);

	mqtt_buff[mqtt_buff_index++] = clientId_size / 256;
	mqtt_buff[mqtt_buff_index++] = clientId_size % 256;
	memcpy(mqtt_buff + mqtt_buff_index, clientId, clientId_size);
	mqtt_buff_index += clientId_size;

	mqtt_buff[mqtt_buff_index++] = username_size / 256;
	mqtt_buff[mqtt_buff_index++] = username_size % 256;
	memcpy(mqtt_buff + mqtt_buff_index, username, username_size);
	mqtt_buff_index += username_size;

	mqtt_buff[mqtt_buff_index++] = password_size / 256;
	mqtt_buff[mqtt_buff_index++] = password_size % 256;
	memcpy(mqtt_buff + mqtt_buff_index, password, password_size);
	mqtt_buff_index += password_size;

	// 验证数据
	// for (int i = 0; i < mqtt_buff_index; i++) {
	// 	u1_printf("%02x ", mqtt_buff[i]);
	// }
	// u1_printf("\r\n");
	mqtt_deal_tx_data(mqtt_buff, mqtt_buff_index);
}

void mqtt_subscribe_message(const char *topic_name, int QoS) {
	bzero(mqtt_buff, sizeof(mqtt_buff));
	uint8_t mqtt_buff_index = 0;
	mqtt_buff[mqtt_buff_index++] = 0x82;

	// 有效载荷初始长度
	uint16_t payload_len = 2 + strlen(topic_name) + 1;
	// 可变报头
	uint8_t var_header[2] = {
			0x00, 0x0A          /* 客户端标识符 */
	};

	// 剩余长度
	uint8_t remain_size = sizeof(var_header) + payload_len;

	while (remain_size > 0) {
		int len = remain_size % 128;
		remain_size /= 128;
		if (remain_size) {
			len |= 0x80;
		}
		mqtt_buff[mqtt_buff_index++] = len;
	}

	memcpy(mqtt_buff + mqtt_buff_index, var_header, sizeof(var_header));
	mqtt_buff_index += sizeof(var_header);

	mqtt_buff[mqtt_buff_index++] = strlen(topic_name) / 256;
	mqtt_buff[mqtt_buff_index++] = strlen(topic_name) % 256;
	memcpy(mqtt_buff + mqtt_buff_index, topic_name, strlen(topic_name));
	mqtt_buff_index += strlen(topic_name);
	mqtt_buff[mqtt_buff_index++] = QoS;

	// for (int i = 0; i < strlen(topic_name); i++) {
	// 	u1_printf("%02x ", topic_name[i]);
	// }
	// u1_printf("\r\n");
	// 验证数据
	for (int i = 0; i < mqtt_buff_index; i++) {
		u1_printf("%02x ", mqtt_buff[i]);
	}
	u1_printf("\r\n");
	mqtt_deal_tx_data(mqtt_buff, mqtt_buff_index);
}

void mqtt_ping_message() {
	bzero(mqtt_buff, sizeof(mqtt_buff));
	uint8_t mqtt_buff_index = 0;
	mqtt_buff[mqtt_buff_index++] = 0xC0;
	mqtt_buff[mqtt_buff_index++] = 0x00;
	mqtt_deal_tx_data(mqtt_buff, mqtt_buff_index);
}

void mqtt_deal_tx_data(u_char *data, int size) {
	mqtt_tx_in_ptr[0] = size / 256;
	mqtt_tx_in_ptr[1] = size % 256;
	memcpy(mqtt_tx_in_ptr + 2, data, size);
	mqtt_tx_in_ptr += 400;
	if (mqtt_tx_in_ptr == mqtt_tx_end_ptr) {
		mqtt_tx_in_ptr = mqtt_tx_buff[0];
	}
}