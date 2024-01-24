#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x04, 0x03, 0x02, 0x01};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	OLED_Init();
	rtc_init();
	OLED_ShowString(1, 1, "Date: XXXX-XX-XX");
	OLED_ShowString(2, 1, "Time: XX:XX:XX");
	OLED_ShowString(3, 1, "CNT : ");
	while (1) {
		get_time();

		OLED_ShowNum(1, 7, local_time.tm_year + 1900, 4);
		OLED_ShowNum(1, 12, local_time.tm_mon + 1, 2);
		OLED_ShowNum(1, 15, local_time.tm_mday, 2);
		OLED_ShowNum(2, 7, local_time.tm_hour + 8, 2);
		OLED_ShowNum(2, 10, local_time.tm_min, 2);
		OLED_ShowNum(2, 13, local_time.tm_sec, 2);
		OLED_ShowNum(3, 7, RTC_GetCounter(), 10);
	}
}

void TIM2_IRQHandler() {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
