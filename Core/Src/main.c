#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x04, 0x03, 0x02, 0x01};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
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

	while (1) {

	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
