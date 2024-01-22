#ifndef STM32_STD_W25Q64_HARDWARE_H
#define STM32_STD_W25Q64_HARDWARE_H

#include "spi_hardware.h"

#define W25Q64_WRITE_ENABLE							0x06
#define W25Q64_WRITE_DISABLE						0x04
#define W25Q64_READ_STATUS_REGISTER_1				0x05
#define W25Q64_READ_STATUS_REGISTER_2				0x35
#define W25Q64_WRITE_STATUS_REGISTER				0x01
#define W25Q64_PAGE_PROGRAM							0x02
#define W25Q64_QUAD_PAGE_PROGRAM					0x32
#define W25Q64_BLOCK_ERASE_64KB						0xD8
#define W25Q64_BLOCK_ERASE_32KB						0x52
#define W25Q64_SECTOR_ERASE_4KB						0x20
#define W25Q64_CHIP_ERASE							0xC7
#define W25Q64_ERASE_SUSPEND						0x75
#define W25Q64_ERASE_RESUME							0x7A
#define W25Q64_POWER_DOWN							0xB9
#define W25Q64_HIGH_PERFORMANCE_MODE				0xA3
#define W25Q64_CONTINUOUS_READ_MODE_RESET			0xFF
#define W25Q64_RELEASE_POWER_DOWN_HPM_DEVICE_ID		0xAB
#define W25Q64_MANUFACTURER_DEVICE_ID				0x90
#define W25Q64_READ_UNIQUE_ID						0x4B
#define W25Q64_JEDEC_ID								0x9F
#define W25Q64_READ_DATA							0x03
#define W25Q64_FAST_READ							0x0B
#define W25Q64_FAST_READ_DUAL_OUTPUT				0x3B
#define W25Q64_FAST_READ_DUAL_IO					0xBB
#define W25Q64_FAST_READ_QUAD_OUTPUT				0x6B
#define W25Q64_FAST_READ_QUAD_IO					0xEB
#define W25Q64_OCTAL_WORD_READ_QUAD_IO				0xE3

#define W25Q64_DUMMY_BYTE							0xFF

/*
	OLED_Init();
	w25q64_hardware_init();

	uint8_t MID;
	uint16_t DID;
	w25q64_hardware_read_id(&MID, &DID);
	OLED_ShowHexNum(1, 1, MID, 2);
	OLED_ShowHexNum(1, 8, DID, 4);

	uint32_t address = 0x000000;
	w25q64_hardware_sector_erase(address);
	w25q64_hardware_page_program(address, data_1, 4);
	w25q64_hardware_read_data(address, data_2, 4);
	OLED_ShowHexNum(2, 1, data_2[0], 2);
	OLED_ShowHexNum(2, 4, data_2[1], 2);
	OLED_ShowHexNum(2, 7, data_2[2], 2);
	OLED_ShowHexNum(2, 10, data_2[3], 2);
	// w25q64_hardware_sector_erase(address);
	// w25q64_hardware_read_data(address, data_2, 4);
	// OLED_ShowHexNum(3, 1, data_2[0], 2);
	// OLED_ShowHexNum(3, 4, data_2[1], 2);
	// OLED_ShowHexNum(3, 7, data_2[2], 2);
	// OLED_ShowHexNum(3, 10, data_2[3], 2);
 */
void w25q64_hardware_init();
void w25q64_hardware_read_id(uint8_t *MID, uint16_t *DID);
void w25q64_hardware_write_enable();
void w25q64_hardware_wait_busy();
void w25q64_hardware_page_program(uint32_t address, uint8_t *data_array, uint16_t count);
void w25q64_hardware_sector_erase(uint32_t address);
void w25q64_hardware_read_data(uint32_t address, uint8_t *data_array, uint32_t count);

#endif //STM32_STD_W25Q64_HARDWARE_H
