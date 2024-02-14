#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x04, 0x03, 0x02, 0x01};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	NVIC_Config();
	OLED_Init();
	My_USART1();
	My_USART2();
	dht11_init();

	mqtt_data_init();
	mqtt_connect_message();
	while (1) {
		delay_s(1);
		// u1_printf("Hello, World\r\n");
		int8_t temp[2], htmi[2];
		dht11_read_data(temp, temp + 1, htmi, htmi + 1);
		OLED_ShowNum(1, 1, temp[0], 2);
		OLED_ShowChar(1, 3, '.');
		OLED_ShowNum(1, 4, temp[1], 1);
		OLED_ShowNum(2, 1, htmi[0], 2);
		OLED_ShowChar(2, 3, '.');
		OLED_ShowNum(2, 4, htmi[1], 1);
	}
}

void TIM2_IRQHandler() {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void NVIC_Config() {
	NVIC_InitTypeDef nvicInitTypeDef;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	nvicInitTypeDef.NVIC_IRQChannel = USART2_IRQn;
	nvicInitTypeDef.NVIC_IRQChannelCmd = ENABLE;
	nvicInitTypeDef.NVIC_IRQChannelSubPriority = 0;
	nvicInitTypeDef.NVIC_IRQChannelPreemptionPriority = 0;

	NVIC_Init(&nvicInitTypeDef);
}