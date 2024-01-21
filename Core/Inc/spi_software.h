#ifndef STM32_STD_SPI_SOFTWARE_H
#define STM32_STD_SPI_SOFTWARE_H

#include "main.h"

void spi_software_init();
void spi_software_strat();
void spi_software_stop();
uint8_t spi_software_swap_byte(uint8_t byte_send);

#endif //STM32_STD_SPI_SOFTWARE_H
