#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x04, 0x03, 0x02, 0x01};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	OLED_Init();
	My_USART1();
	My_USART2();
	TIM2_Init(30000 - 1, 36000 - 1);
	TIM3_Init(60000 - 1, 36000 - 1);
	TIM4_Init(400 - 1, 7200 - 1);
	dht11_init();

	NVIC_Config();

	while (1) {
		int8_t temp[2], htmi[2];
		dht11_read_data(temp, temp + 1, htmi, htmi + 1);
		OLED_ShowNum(1, 1, temp[0], 2);
		OLED_ShowChar(1, 3, '.');
		OLED_ShowNum(1, 4, temp[1], 1);
		OLED_ShowNum(2, 1, htmi[0], 2);
		OLED_ShowChar(2, 3, '.');
		OLED_ShowNum(2, 4, htmi[1], 1);
		if (connect_flag == 0) {
			memset(WiFi_RX_BUF, 0, sizeof(WiFi_RX_BUF));
			WiFi_RxCounter = 0;
			TIM_Cmd(TIM4, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			TIM_Cmd(TIM2, DISABLE);
			u1_printf("正在连接 MQTT 服务器\r\n");
			if (wifi_connect(SERVER_IP, SERVER_PORT) == 0) {
				connect_flag = 1;
				u1_printf("已连接 MQTT 服务器\r\n");
				memset(WiFi_RX_BUF, 0, sizeof(WiFi_RX_BUF));
				WiFi_RxCounter = 0;
				mqtt_data_init();
				mqtt_connect_message();
			}
		} else {
			if (mqtt_tx_out_ptr != mqtt_tx_in_ptr) {
				// if (mqtt_tx_out_ptr[2] == 0x10
				//     || (mqtt_tx_out_ptr[2] == 0x82 && connect_pack_flag)
				//     || subscribe_flag) {
				// 	u1_printf("报文类型 %x\r\n", mqtt_tx_out_ptr[2]);
				// 	mqtt_tx_data(mqtt_tx_out_ptr);
				// 	mqtt_tx_out_ptr += 400;
				// 	if (mqtt_tx_out_ptr == mqtt_tx_end_ptr) {
				// 		mqtt_tx_out_ptr = mqtt_tx_buff[0];
				// 	}
				// }
				u1_printf("报文类型 %x\r\n", mqtt_tx_out_ptr[2]);
				mqtt_tx_data(mqtt_tx_out_ptr);
				mqtt_tx_out_ptr += 400;
				if (mqtt_tx_out_ptr == mqtt_tx_end_ptr) {
					mqtt_tx_out_ptr = mqtt_tx_buff[0];
				}
			}

			if (mqtt_rx_out_ptr != mqtt_rx_in_ptr) {
				if ((int) mqtt_rx_out_ptr[2] == 0x20) {
					switch (mqtt_rx_out_ptr[5]) {
						case 0x00:
							u1_printf("CONNECT 报文发送成功\r\n");
							connect_pack_flag = 1;
							mqtt_subscribe_message(TopicName, 0);
							break;
						case 0x01:
							u1_printf("0x01连接已拒绝，不支持的协议版本，准备重启\r\n");
							mqtt_flag_re_init();
							break;
						case 0x02:
							u1_printf("0x02连接已拒绝，不合格的客户 端标识符，准备重启\r\n");
							mqtt_flag_re_init();
							break;
						case 0x03:
							u1_printf("0x03连接已拒绝，服务端不可用，准备重启\r\n");
							mqtt_flag_re_init();
							break;
						case 0x04:
							u1_printf("0x04连接已拒绝，无效的用户名 或密码，准备重启\r\n");
							mqtt_flag_re_init();
							break;
						case 0x05:
							u1_printf("0x05连接已拒绝，未授权，准备重启\r\n");
							mqtt_flag_re_init();
							break;
						default:
							u1_printf("连接已拒绝，准备重启\r\n");
							mqtt_flag_re_init();
							break;
					}
				} else if ((int) mqtt_rx_out_ptr[2] == 0x90) {
					switch (mqtt_rx_out_ptr[6]) {
						case 0x01:
							u1_printf("订阅成功\r\n");
							subscribe_flag = 1;
							ping_flag = 0;
							TIM_Cmd(TIM3, ENABLE);
							TIM_Cmd(TIM2, ENABLE);
							break;
						default:
							u1_printf("订阅失败\r\n");
							mqtt_flag_re_init();
							break;
					}
				} else if ((int) mqtt_rx_out_ptr[2] == 0xD0) {
					u1_printf("心跳检测正常\r\n");
					if (ping_flag == 1) {
						ping_flag = 0;
					} else if (ping_flag > 1) {
						ping_flag = 0;
						TIM3_Init(60000 - 1, 36000 - 1);
						TIM_Cmd(TIM3, ENABLE);
					}
				}
				mqtt_rx_out_ptr += 400;
				if (mqtt_rx_out_ptr == mqtt_rx_end_ptr) {
					mqtt_rx_out_ptr = mqtt_rx_buff[0];
				}
			}
		}
	}
}

// void TIM2_IRQHandler() {
// 	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
// 		num++;
// 		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
// 	}
// }

void NVIC_Config() {
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// 串口 2
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	// 判断是否是一条消息
	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	// 心跳检测
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	// 推送消息
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}