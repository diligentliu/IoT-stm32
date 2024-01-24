#ifndef STM32_STD_RTC_H
#define STM32_STD_RTC_H

#include "stm32f10x.h"
#include "time.h"

/*
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
 */
extern struct tm local_time;
void rtc_init();
void get_time();
void set_time();

#endif //STM32_STD_RTC_H
