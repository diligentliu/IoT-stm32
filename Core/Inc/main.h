#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>

#include "stm32f10x_it.h"
#include "count_sensor.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "rotate_encoder.h"
#include "timer.h"
#include "outer_timer.h"
#include "pwm.h"
#include "breathing_light.h"
#include "servos.h"
#include "input_capture.h"
#include "ad.h"
#include "dma_data_transfer.h"
#include "serial.h"
#include "i2c_software.h"
#include "MPU6050.h"
#include "i2c_hardware.h"
#include "spi_software.h"
#include "w25q64_software.h"
#include "spi_hardware.h"
#include "w25q64_hardware.h"
#include "rtc.h"
#include "dht11.h"
#include "my_usart1.h"
#include "my_usart2.h"
#include "wifi.h"
#include "utils_hmac.h"
#include "utils_md5.h"
#include "utils_sha1.h"
#include "mqtt.h"
#include "tim_4.h"
#include "tim_3.h"
#include "tim_2.h"

void NVIC_Config();
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
