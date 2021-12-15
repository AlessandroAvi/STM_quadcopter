#include <MPU6050.h>
#include "i2c.h"

double angle_x = 0;
double angle_y = 0;
double angle_z = 0;

int millis=0;
int start_time=0;
uint16_t iter=0;
int STOP_REC_FLAG = 0;

uint8_t MPU_STATE=0;

double avrg_gX = 0;
double avrg_gY = 0;
double avrg_gZ = 0;

void MPU6050_Init(void){
	uint8_t check;
	check = 0;

	uint8_t data;

	// Reads from address if device is connected
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 500);
	start_time = HAL_GetTick();

	if(check == 104){
		msgLen = sprintf(msgDebug, "MPU6050 initialized");
		HAL_UART_Transmit(&huart2, (uint8_t*)msgDebug, msgLen , 50);

		// exit SLEEP mode  and set clock to 8 MHz
		data=0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 500);

		// sample frequency = 8 kHZ / (data +1)
		data = 0X07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 500);

		// set the MPU digital low pass filter to 250 Hz
		data = 0X01;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, CONFIG, 1, &data, 1, 500);

		// Set up the IMU config
		// set up the IMU to AFS_SEL 0 and full scale +- 2g
		// if set to 1 set the IMU to auto test
		data = 0x02;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 500);


		// Set up the GYRO config - pag 14
		// set up the GYRO to AFS_SEL 0 and full scale +- 500°
		data = 0x01;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 500);
	}
	MPU_STATE = 1;
}




// Read ACCELEROMETER data
void MPU6050_ReadAcc(void){

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, rec_data1, 6, 500);

	acc_X_raw = (int16_t)(rec_data1[0] << 8 | rec_data1[1]);
	acc_Y_raw = (int16_t)(rec_data1[2] << 8 | rec_data1[3]);
	acc_Z_raw = (int16_t)(rec_data1[4] << 8 | rec_data1[5]);

	// pag 29, because of full scale range selected before
	ax = acc_X_raw/4096;
	ay = acc_Y_raw/4096;
	az = acc_Z_raw/4096; //16384
}


void MPU6050_ReadGyro(void){

	if(MPU_STATE == 0) return;

	millis = HAL_GetTick()-start_time;

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, rec_data2, 6, 500);

	gyro_X_raw = (int16_t)(rec_data2[0] << 8 | rec_data2[1]);
	gyro_Y_raw = (int16_t)(rec_data2[2] << 8 | rec_data2[3]);
	gyro_Z_raw = (int16_t)(rec_data2[4] << 8 | rec_data2[5]);

	gyro_X_scaled = gyro_X_raw/65.5;
	gyro_Y_scaled = gyro_Y_raw/65.5;
	gyro_Z_scaled = gyro_Z_raw/65.5;



	if(iter<1000){
		iter += 1;

		avrg_gX = gyro_X_scaled+avrg_gX;
		avrg_gY = gyro_Y_scaled+avrg_gY;
		avrg_gZ = gyro_Z_scaled+avrg_gZ;
	}else{
		// Integrate de noised angular rate by the sampling time
		angle_x += (gyro_X_scaled-avrg_gX/iter)*0.004;
		angle_y += (gyro_Y_scaled-avrg_gY/iter)*0.004;
		angle_z += (gyro_Z_scaled-avrg_gZ/iter)*0.004;
	}


	/*
	if(STOP_REC_FLAG == 0 && iter < REC_SIZE*SAMPL_FREQ){
		arr_time[iter] = millis;
		arr_gx[iter] = gx;
		arr_gy[iter] = gy;
		arr_gz[iter] = gz;
		iter += 1;
	}else{
		STOP_REC_FLAG = 1;
		iter = 0;
		start_time = HAL_GetTick();
	}
	*/



}
