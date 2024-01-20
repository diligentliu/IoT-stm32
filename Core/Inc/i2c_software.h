#ifndef STM32_STD_I2C_SOFTWARE_H
#define STM32_STD_I2C_SOFTWARE_H

#include "main.h"

#define SCL_PORT    GPIOB
#define SCL_PIN     GPIO_Pin_10
#define SDA_PORT    GPIOB
#define SDA_PIN     GPIO_Pin_11

void i2c_software_init();
void i2c_software_start();
void i2c_software_stop();
void i2c_software_send_byte(uint8_t byte);
uint8_t i2c_software_receive_byte();
void i2c_software_send_ack(uint8_t byte);
uint8_t i2c_software_receive_ack();

#endif //STM32_STD_I2C_SOFTWARE_H
