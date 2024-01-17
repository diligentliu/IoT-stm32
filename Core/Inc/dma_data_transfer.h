#ifndef STM32_STD_DMA_DATA_TRANSFER_H
#define STM32_STD_DMA_DATA_TRANSFER_H

#include "main.h"

/**
	OLED_Init();
	dma_data_transfer_init((uint32_t) data_1, (uint32_t) data_2, 4);

	OLED_ShowHexNum(1, 1, data_1[0], 2);
	OLED_ShowHexNum(1, 4, data_1[1], 2);
	OLED_ShowHexNum(1, 7, data_1[2], 2);
	OLED_ShowHexNum(1,10, data_1[3], 2);

	OLED_ShowHexNum(2, 1, data_2[0], 2);
	OLED_ShowHexNum(2, 4, data_2[1], 2);
	OLED_ShowHexNum(2, 7, data_2[2], 2);
	OLED_ShowHexNum(2,10, data_2[3], 2);

	while (1) {
		data_1[0]++;
		data_1[1]++;
		data_1[2]++;
		data_1[3]++;

		OLED_ShowHexNum(1, 1, data_1[0], 2);
		OLED_ShowHexNum(1, 4, data_1[1], 2);
		OLED_ShowHexNum(1, 7, data_1[2], 2);
		OLED_ShowHexNum(1,10, data_1[3], 2);

		OLED_ShowHexNum(2, 1, data_2[0], 2);
		OLED_ShowHexNum(2, 4, data_2[1], 2);
		OLED_ShowHexNum(2, 7, data_2[2], 2);
		OLED_ShowHexNum(2,10, data_2[3], 2);

		delay_ms(1000);
		dma_data_transfer();
	}
 * @param addr_from 源地址
 * @param addr_to   目的地址
 * @param size      转运次数
 */
void dma_data_transfer_init(uint32_t addr_from, uint32_t addr_to, uint16_t size);
void dma_data_transfer();

#endif //STM32_STD_DMA_DATA_TRANSFER_H
