/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

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

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
