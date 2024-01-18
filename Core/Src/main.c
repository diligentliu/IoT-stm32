#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x01, 0x02, 0x03, 0x04};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	OLED_Init();
	serial_init();
	serial_send_byte(0x41);

	uint8_t array[8];
	for (int i = 0; i < 8; ++i) {
		array[i] = 'a' + i;
	}
	serial_send_array(array, 8);
	const char *string = "我可以是中文嘛？";
	serial_send_string(string);
	serial_send_number(9999, 4);

	printf("Num = %d\r\n", 666);

	while (1) {
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
			uint8_t data = USART_ReceiveData(USART1);
			OLED_ShowHexNum(1, 1, data, 2);
		}
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
