#ifndef STM32_STD_RTC_H
#define STM32_STD_RTC_H

#include "main.h"
#include "time.h"

extern struct tm local_time;
void rtc_init();
void get_time();
void set_time();
void rtc_test();

#endif //STM32_STD_RTC_H
