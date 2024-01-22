#ifndef STM32_STD_SPI_HARDWARE_H
#define STM32_STD_SPI_HARDWARE_H

#include "main.h"

void spi_hardware_init();
void spi_hardware_strat();
void spi_hardware_stop();
uint8_t spi_hardware_swap_byte(uint8_t byte_send);

#endif //STM32_STD_SPI_HARDWARE_H
