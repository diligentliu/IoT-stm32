#include "w25q64_hardware.h"

void w25q64_hardware_init() {
	spi_hardware_init();
}

void w25q64_hardware_read_id(uint8_t *MID, uint16_t *DID) {
	spi_hardware_strat();
	spi_hardware_swap_byte(W25Q64_JEDEC_ID);
	*MID = spi_hardware_swap_byte(W25Q64_DUMMY_BYTE);
	*DID = (spi_hardware_swap_byte(W25Q64_DUMMY_BYTE) << 8)
	       | spi_hardware_swap_byte(W25Q64_DUMMY_BYTE);
	spi_hardware_stop();
}

void w25q64_hardware_write_enable() {
	spi_hardware_strat();
	spi_hardware_swap_byte(W25Q64_WRITE_ENABLE);
	spi_hardware_stop();
}

void w25q64_hardware_wait_busy() {
	spi_hardware_strat();
	spi_hardware_swap_byte(W25Q64_READ_STATUS_REGISTER_1);
	while (spi_hardware_swap_byte(W25Q64_DUMMY_BYTE) & 1);
	spi_hardware_stop();
}

void w25q64_hardware_page_program(uint32_t address, uint8_t *data_array, uint16_t count) {
	w25q64_hardware_write_enable();

	spi_hardware_strat();
	spi_hardware_swap_byte(W25Q64_PAGE_PROGRAM);
	spi_hardware_swap_byte(address >> 16);
	spi_hardware_swap_byte(address >> 8);
	spi_hardware_swap_byte(address);
	for (uint16_t i = 0; i < count; ++i) {
		spi_hardware_swap_byte(data_array[i]);
	}
	spi_hardware_stop();

	w25q64_hardware_wait_busy();
}

void w25q64_hardware_sector_erase(uint32_t address) {
	w25q64_hardware_write_enable();

	spi_hardware_strat();
	spi_hardware_swap_byte(W25Q64_SECTOR_ERASE_4KB);
	spi_hardware_swap_byte(address >> 16);
	spi_hardware_swap_byte(address >> 8);
	spi_hardware_swap_byte(address);
	spi_hardware_stop();

	w25q64_hardware_wait_busy();
}

void w25q64_hardware_read_data(uint32_t address, uint8_t *data_array, uint32_t count) {
	spi_hardware_strat();
	spi_hardware_swap_byte(W25Q64_READ_DATA);
	spi_hardware_swap_byte(address >> 16);
	spi_hardware_swap_byte(address >> 8);
	spi_hardware_swap_byte(address);
	for (uint32_t i = 0; i < count; ++i) {
		data_array[i] = spi_hardware_swap_byte(W25Q64_DUMMY_BYTE);
	}
	spi_hardware_stop();
}