#include <MPU6050.h>
#include "i2c.h"

int millis=0;
int start_time=0;
uint16_t iter=0;


double avrg_gX = 0;
double avrg_gY = 0;
double avrg_gZ = 0;

IMU_STATE GYRO_STATE = 0;
IMU_STATE ACC_STATE = 0;

int ACC_SCALE_FACTOR = 4096;
double GYRO_SCALE_FACTOR = 65.5;







void MPU6050_Init(IMU_MEASURE * MPU_measure){

	uint8_t check = 0;
	uint8_t data;

	// Reads from address if device is connected
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 500);

	if(check == 104){
		PRINTF("MPU6050 initialized \n\r");

		// exit SLEEP mode
		data=0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 500);

		// sample frequency = 8 kHZ
		data = 0X07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 500);

		// set the MPU digital low pass filter to 250 Hz
		data = 0X01;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, CONFIG, 1, &data, 1, 500);

		// Set up the IMU config (full scale and auto test)
		data = 0x02;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 500);


		// Set up the GYRO config (full scale)
		data = 0x01;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 500);

		GYRO_STATE = 1;
		ACC_STATE = 1;

		MPU_measure-> angle_X = 0;
		MPU_measure-> angle_Y = 0;
		MPU_measure-> angle_Z = 0;
	}
}




// Read ACCELEROMETER data
void MPU6050_ReadAcc(IMU_MEASURE * MPU_measure){

	if(ACC_STATE == DISABLED) return;

	// read data
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, rec_data1, 6, 500);

	// parse data
	acc_X_raw = (int16_t)(rec_data1[0] << 8 | rec_data1[1]);
	acc_Y_raw = (int16_t)(rec_data1[2] << 8 | rec_data1[3]);
	acc_Z_raw = (int16_t)(rec_data1[4] << 8 | rec_data1[5]);

	// scale data
	MPU_measure->acc_X = acc_X_raw/ACC_SCALE_FACTOR;
	MPU_measure->acc_Y = acc_Y_raw/ACC_SCALE_FACTOR;
	MPU_measure->acc_Z = acc_Z_raw/ACC_SCALE_FACTOR;
}






void MPU6050_ReadGyro(IMU_MEASURE * MPU6050_measure){

	if(GYRO_STATE == DISABLED) return;

	// read data
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, rec_data2, 6, 500);

	// parse data
	gyro_X_raw = (int16_t)(rec_data2[0] << 8 | rec_data2[1]);
	gyro_Y_raw = (int16_t)(rec_data2[2] << 8 | rec_data2[3]);
	gyro_Z_raw = (int16_t)(rec_data2[4] << 8 | rec_data2[5]);

	// scale data
	gyro_X_scaled = gyro_X_raw/GYRO_SCALE_FACTOR;
	gyro_Y_scaled = gyro_Y_raw/GYRO_SCALE_FACTOR;
	gyro_Z_scaled = gyro_Z_raw/GYRO_SCALE_FACTOR;


	// either calibrate or compute angle
	if(GYRO_STATE == CALIBRATION){
		iter += 1;

		avrg_gX = gyro_X_scaled+avrg_gX;
		avrg_gY = gyro_Y_scaled+avrg_gY;
		avrg_gZ = gyro_Z_scaled+avrg_gZ;

		if(iter == CALIBRATION_TIME*SAMPL_FREQ){
			avrg_gX = avrg_gX/iter;
			avrg_gY = avrg_gY/iter;
			avrg_gZ = avrg_gZ/iter;
			GYRO_STATE = READY;

			PRINTF("MPU6050 READY TO USE \n\r");
		}

	}else if(GYRO_STATE == READY){

		double tmp_X = (gyro_X_scaled-avrg_gX)/SAMPL_FREQ;
		double tmp_Y = (gyro_Y_scaled-avrg_gY)/SAMPL_FREQ;
		double tmp_Z = (gyro_Z_scaled-avrg_gZ)/SAMPL_FREQ;

		MPU6050_measure->angle_dX = gyro_X_scaled-avrg_gX;
		MPU6050_measure->angle_dY = gyro_Y_scaled-avrg_gY;
		MPU6050_measure->angle_dZ = gyro_Z_scaled-avrg_gZ;

		// x -> pitch | y -> roll | z -> yaw
		MPU6050_measure->angle_X += tmp_X ;
		MPU6050_measure->angle_Y += tmp_Y ;
		MPU6050_measure->angle_Z += tmp_Z;
	}
}
