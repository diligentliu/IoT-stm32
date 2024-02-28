#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x04, 0x03, 0x02, 0x01};
uint8_t data_2[] = {0, 0, 0, 0};
extern int8_t connect_flag;

int main(void) {
	OLED_Init();
	My_USART1();
	My_USART2();
	TIM4_Init(400 - 1, 7200 - 1);
	dht11_init();

	NVIC_Config();

	while (1) {
		// delay_s(1);
		// u1_printf("Hello, World\r\n");
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
				if (mqtt_tx_out_ptr[2] == 0x10) {
					mqtt_tx_data(mqtt_tx_out_ptr);
					mqtt_tx_out_ptr += 400;
					if (mqtt_tx_out_ptr == mqtt_tx_end_ptr) {
						mqtt_tx_out_ptr = mqtt_tx_buff[0];
					}
				}
			}
			if (mqtt_rx_out_ptr != mqtt_rx_in_ptr) {
				if ((int) mqtt_rx_out_ptr[2] == 0x20) {
					switch (mqtt_rx_out_ptr[5]) {
						case 0x00:
							u1_printf("CONNECT 报文连接成功");
							break;
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

void TIM2_IRQHandler() {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void NVIC_Config() {
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}