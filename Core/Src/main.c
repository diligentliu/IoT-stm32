#include "main.h"

int16_t num = 0;
uint8_t data_1[] = {0x01, 0x02, 0x03, 0x04};
uint8_t data_2[] = {0, 0, 0, 0};

int main(void) {
	OLED_Init();
	mpu6050_init();

	int16_t acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z;
	uint8_t id = mpu6050_r_reg(MPU6050_WHO_AM_I);
	OLED_ShowHexNum(1, 1, id, 2);
	while (1) {
		mpu6050_get_data(&acc_x, &acc_y, &acc_z, &gyro_x, &gyro_y, &gyro_z);
		OLED_ShowSignedNum(2, 1, acc_x, 5);
		OLED_ShowSignedNum(3, 1, acc_y, 5);
		OLED_ShowSignedNum(4, 1, acc_z, 5);
		OLED_ShowSignedNum(2, 8, gyro_x, 5);
		OLED_ShowSignedNum(3, 8, gyro_y, 5);
		OLED_ShowSignedNum(4, 8, gyro_z, 5);
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
