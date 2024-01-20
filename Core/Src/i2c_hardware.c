#include "i2c_hardware.h"

void wait_event(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT) {
	uint32_t time_out = 10000;
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS) {
		--time_out;
		if (time_out == 0) {
			OLED_Init();
			OLED_ShowString(1, 1, "Error");
			break;
		}
	}
}

void i2c_hardware_w_reg(uint8_t reg_address, uint8_t data) {
	I2C_GenerateSTART(I2C2, ENABLE);
	wait_event(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	wait_event(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

	I2C_SendData(I2C2, reg_address);
	wait_event(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

	I2C_SendData(I2C2, data);
	wait_event(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

	I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t i2c_hardware_r_reg(uint8_t reg_address) {
	I2C_GenerateSTART(I2C2, ENABLE);
	wait_event(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	wait_event(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

	I2C_SendData(I2C2, reg_address);
	wait_event(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

	I2C_GenerateSTART(I2C2, ENABLE);
	wait_event(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
	wait_event(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

	I2C_AcknowledgeConfig(I2C2, DISABLE);
	I2C_GenerateSTOP(I2C2, ENABLE);
	wait_event(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);

	uint8_t data = I2C_ReceiveData(I2C2);
	I2C_AcknowledgeConfig(I2C2, ENABLE);

	return data;
}

void i2c_hardware_mpu6050_get_data(int16_t *acc_x, int16_t *acc_y, int16_t *acc_z, int16_t *gyro_x, int16_t *gyro_y,
                                   int16_t *gyro_z) {
	*acc_x = (((int16_t) i2c_hardware_r_reg(MPU6050_ACCEL_XOUT_H)) << 8)
	         | i2c_hardware_r_reg(MPU6050_ACCEL_XOUT_L);
	*acc_y = (((int16_t) i2c_hardware_r_reg(MPU6050_ACCEL_YOUT_H)) << 8)
	         | i2c_hardware_r_reg(MPU6050_ACCEL_YOUT_L);
	*acc_z = (((int16_t) i2c_hardware_r_reg(MPU6050_ACCEL_ZOUT_H)) << 8)
	         | i2c_hardware_r_reg(MPU6050_ACCEL_ZOUT_L);
	*gyro_x = (((int16_t) i2c_hardware_r_reg(MPU6050_GYRO_XOUT_H)) << 8)
	          | i2c_hardware_r_reg(MPU6050_GYRO_XOUT_L);
	*gyro_y = (((int16_t) i2c_hardware_r_reg(MPU6050_GYRO_YOUT_H)) << 8)
	          | i2c_hardware_r_reg(MPU6050_GYRO_YOUT_L);
	*gyro_z = (((int16_t) i2c_hardware_r_reg(MPU6050_GYRO_ZOUT_H)) << 8)
	          | i2c_hardware_r_reg(MPU6050_GYRO_ZOUT_L);
}

void i2c_hardware_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef gpioInitTypeDef;
	gpioInitTypeDef.GPIO_Mode = GPIO_Mode_AF_OD;
	gpioInitTypeDef.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	gpioInitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInitTypeDef);

	I2C_InitTypeDef i2CInitTypeDef;
	i2CInitTypeDef.I2C_Mode = I2C_Mode_I2C;
	i2CInitTypeDef.I2C_ClockSpeed = 50000;
	i2CInitTypeDef.I2C_DutyCycle = I2C_DutyCycle_2;
	i2CInitTypeDef.I2C_Ack = I2C_Ack_Enable;
	i2CInitTypeDef.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2CInitTypeDef.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C2, &i2CInitTypeDef);

	I2C_Cmd(I2C2, ENABLE);

	i2c_hardware_w_reg(MPU6050_PWR_MGMT_1, 0x01);
	i2c_hardware_w_reg(MPU6050_PWR_MGMT_2, 0x00);
	i2c_hardware_w_reg(MPU6050_SMPLRT_DIV, 0x09);
	i2c_hardware_w_reg(MPU6050_CONFIG, 0x06);
	i2c_hardware_w_reg(MPU6050_GYRO_CONFIG, 0x18);
	i2c_hardware_w_reg(MPU6050_ACCEL_CONFIG, 0x18);
}
