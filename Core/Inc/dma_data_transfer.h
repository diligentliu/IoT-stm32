#ifndef STM32_STD_DMA_DATA_TRANSFER_H
#define STM32_STD_DMA_DATA_TRANSFER_H

#include "main.h"

void dma_data_transfer_init(uint32_t addr_from, uint32_t addr_to, uint16_t size);
void dma_data_transfer();

#endif //STM32_STD_DMA_DATA_TRANSFER_H
