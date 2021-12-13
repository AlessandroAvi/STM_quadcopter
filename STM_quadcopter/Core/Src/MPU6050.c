#include <MPU6050.h>
#include "i2c.h"


void MPU6050_Init(void){
	uint8_t check;
	check = 0;

	uint8_t data;

	// Reads from address if device is connected
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 500);

	if(check == 104){

		msg_len = sprintf(msg_debug, "MPU6050 initialized");
		HAL_UART_Transmit(&huart2, (uint8_t*)msg_debug, msg_len , 50);

		// enable slave mode of the device
		data=0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 500);

		// specify sample frequency
		data = 0X07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 500);

		// Set up the IMU config
		// set up the IMU to AFS_SEL 0 and full scale +- 2g
		// if set to 1 set the IMU to auto test
		data = 0x00;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 500);


		// Set up the GYRO config - pag 14
		// set up the GYRO to AFS_SEL 0 and full scale +- 500°
		data = 0x01;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 500);

	}
}




// Read ACCELEROMETER data
void MPU6050_ReadAcc(void){

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, rec_data1, 6, 500);

	acc_X_raw = (int16_t)(rec_data1[0] << 8 | rec_data1[1]);
	acc_Y_raw = (int16_t)(rec_data1[2] << 8 | rec_data1[3]);
	acc_Z_raw = (int16_t)(rec_data1[4] << 8 | rec_data1[5]);

	// pag 29, because of full scale range selected before
	ax = acc_X_raw/16384.0;
	ay = acc_Y_raw/16384.0;
	az = acc_Z_raw/16384.0;
}


void MPU6050_ReadGyro(void){

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, rec_data2, 6, 500);

	gyro_X_raw = (int16_t)(rec_data2[0] << 8 | rec_data2[1]);
	gyro_Y_raw = (int16_t)(rec_data2[2] << 8 | rec_data2[3]);
	gyro_Z_raw = (int16_t)(rec_data2[4] << 8 | rec_data2[5]);

	gx = gyro_X_raw/65.5;
	gy = gyro_Y_raw/65.5;
	gz = gyro_Z_raw/65.5;
}
