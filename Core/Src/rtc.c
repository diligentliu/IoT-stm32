#include "rtc.h"

struct tm local_time;

void rtc_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);

	if (BKP_ReadBackupRegister(BKP_DR1) != 0xAAAA) {
		RCC_LSEConfig(RCC_LSE_ON);
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);

		RTC_WaitForSynchro();
		RTC_WaitForLastTask();

		RTC_SetPrescaler(32768 - 1);
		RTC_WaitForLastTask();

		RTC_SetCounter(1672588795);
		RTC_WaitForLastTask();

		BKP_WriteBackupRegister(BKP_DR1, 0xAAAA);
	} else {
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}

void get_time() {
	time_t time_cnt = RTC_GetCounter();
	local_time = *localtime(&time_cnt);
}

void set_time() {
	time_t time_cnt;
	struct tm time_data;
	time_data = local_time;

	time_cnt = mktime(&time_data);

	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
}

void rtc_test() {
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