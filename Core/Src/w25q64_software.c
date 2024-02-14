#include "w25q64_software.h"

void w25q64_software_init() {
	spi_software_init();
}

void w25q64_software_read_id(uint8_t *MID, uint16_t *DID) {
	spi_software_strat();
	spi_software_swap_byte(W25Q64_JEDEC_ID);
	*MID = spi_software_swap_byte(W25Q64_DUMMY_BYTE);
	*DID = (spi_software_swap_byte(W25Q64_DUMMY_BYTE) << 8)
	       | spi_software_swap_byte(W25Q64_DUMMY_BYTE);
	spi_software_stop();
}

void w25q64_software_write_enable() {
	spi_software_strat();
	spi_software_swap_byte(W25Q64_WRITE_ENABLE);
	spi_software_stop();
}

void w25q64_software_wait_busy() {
	spi_software_strat();
	spi_software_swap_byte(W25Q64_READ_STATUS_REGISTER_1);
	while (spi_software_swap_byte(W25Q64_DUMMY_BYTE) & 1);
	spi_software_stop();
}

void w25q64_software_page_program(uint32_t address, uint8_t *data_array, uint16_t count) {
	w25q64_software_write_enable();

	spi_software_strat();
	spi_software_swap_byte(W25Q64_PAGE_PROGRAM);
	spi_software_swap_byte(address >> 16);
	spi_software_swap_byte(address >> 8);
	spi_software_swap_byte(address);
	for (uint16_t i = 0; i < count; ++i) {
		spi_software_swap_byte(data_array[i]);
	}
	spi_software_stop();

	w25q64_software_wait_busy();
}

void w25q64_software_sector_erase(uint32_t address) {
	w25q64_software_write_enable();

	spi_software_strat();
	spi_software_swap_byte(W25Q64_SECTOR_ERASE_4KB);
	spi_software_swap_byte(address >> 16);
	spi_software_swap_byte(address >> 8);
	spi_software_swap_byte(address);
	spi_software_stop();

	w25q64_software_wait_busy();
}

void w25q64_software_read_data(uint32_t address, uint8_t *data_array, uint32_t count) {
	spi_software_strat();
	spi_software_swap_byte(W25Q64_READ_DATA);
	spi_software_swap_byte(address >> 16);
	spi_software_swap_byte(address >> 8);
	spi_software_swap_byte(address);
	for (uint32_t i = 0; i < count; ++i) {
		data_array[i] = spi_software_swap_byte(W25Q64_DUMMY_BYTE);
	}
	spi_software_stop();
}