#include "MPU6050.h"

void mpu6050_init() {
	i2c_software_init();
	mpu6050_w_reg(MPU6050_PWR_MGMT_1, 0x01);
	mpu6050_w_reg(MPU6050_PWR_MGMT_2, 0x00);
	mpu6050_w_reg(MPU6050_SMPLRT_DIV, 0x09);
	mpu6050_w_reg(MPU6050_CONFIG, 0x06);
	mpu6050_w_reg(MPU6050_GYRO_CONFIG, 0x18);
	mpu6050_w_reg(MPU6050_ACCEL_CONFIG, 0x18);
}

void mpu6050_w_reg(uint8_t reg_address, uint8_t data) {
	i2c_software_start();
	i2c_software_send_byte(MPU6050_ADDRESS);
	i2c_software_receive_ack();

	i2c_software_send_byte(reg_address);
	i2c_software_receive_ack();

	i2c_software_send_byte(data);
	i2c_software_receive_ack();
	i2c_software_stop();
}

uint8_t mpu6050_r_reg(uint8_t reg_address) {
	i2c_software_start();
	i2c_software_send_byte(MPU6050_ADDRESS);
	i2c_software_receive_ack();

	i2c_software_send_byte(reg_address);
	i2c_software_receive_ack();

	i2c_software_start();
	i2c_software_send_byte(MPU6050_ADDRESS | 0x01);
	i2c_software_receive_ack();

	uint8_t data = i2c_software_receive_byte();
	// 这里给 1 应答是告诉主机我已经接受完毕了, 放弃 SDA 发送权
	i2c_software_send_ack(1);
	i2c_software_stop();

	return data;
}

void mpu6050_get_data(int16_t *acc_x, int16_t *acc_y, int16_t *acc_z,
                      int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z) {
	*acc_x = (((int16_t) mpu6050_r_reg(MPU6050_ACCEL_XOUT_H)) << 8)
	         | mpu6050_r_reg(MPU6050_ACCEL_XOUT_L);
	*acc_y = (((int16_t) mpu6050_r_reg(MPU6050_ACCEL_YOUT_H)) << 8)
	         | mpu6050_r_reg(MPU6050_ACCEL_YOUT_L);
	*acc_z = (((int16_t) mpu6050_r_reg(MPU6050_ACCEL_ZOUT_H)) << 8)
	         | mpu6050_r_reg(MPU6050_ACCEL_ZOUT_L);
	*gyro_x = (((int16_t) mpu6050_r_reg(MPU6050_GYRO_XOUT_H)) << 8)
	          | mpu6050_r_reg(MPU6050_GYRO_XOUT_L);
	*gyro_y = (((int16_t) mpu6050_r_reg(MPU6050_GYRO_YOUT_H)) << 8)
	          | mpu6050_r_reg(MPU6050_GYRO_YOUT_L);
	*gyro_z = (((int16_t) mpu6050_r_reg(MPU6050_GYRO_ZOUT_H)) << 8)
	          | mpu6050_r_reg(MPU6050_GYRO_ZOUT_L);
}