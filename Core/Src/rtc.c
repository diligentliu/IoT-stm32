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