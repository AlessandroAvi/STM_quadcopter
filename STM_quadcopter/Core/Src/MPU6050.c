#include <MPU6050.h>
#include "i2c.h"




uint16_t iter_a = 0;

double avrg_aX = 0;
double avrg_aY = 0;
double avrg_aZ = 0;

IMU_STATE ACC_STATE = DISABLED;




uint16_t iter_g = 0;

double avrg_gX = 0;
double avrg_gY = 0;
double avrg_gZ = 0;

IMU_STATE GYRO_STATE = DISABLED;







void MPU6050_Init(void){

	uint8_t check = 0;
	uint8_t data;

	// Reads from address if device is connected
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 500);

	if(check == 104){
		//PRINTF("MPU6050 initialized \n\r");

		// exit SLEEP mode
		data=0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 500);

		// sample frequency = 8 kHZ
		data = 0X07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 500);

		// set the MPU digital low pass filter to 250 Hz
		//data = 0X01;
		//HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, CONFIG, 1, &data, 1, 500);

		// Set up the ACC config (full scale and auto test)
		data = 0x08;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 500);


		// Set up the GYRO config (full scale)
		data = 0x08;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 500);

		GYRO_STATE = READY;
		ACC_STATE = READY;
	}
}


void MPU6050_Reset(IMU_MEASURE * measures){

	// Measures from the accelerometer
	measures->acc_X = 0;
	measures->acc_Y = 0;
	measures->acc_Z = 0;

	measures->acc_angle_X = 0;
	measures->acc_angle_Y = 0;
	measures->acc_angle_Z = 0;

	// Measures from the gyroscope
	measures->gyro_X = 0;
	measures->gyro_Y = 0;
	measures->gyro_Z = 0;

	measures->gyro_angle_X = 0;
	measures->gyro_angle_Y = 0;
	measures->gyro_angle_Z = 0;

	// Angle measure after the sensor fusion
	measures->angle_X = 0;
	measures->angle_Y = 0;
	measures->angle_Z = 0;
}


// Read ACCELEROMETER data
void MPU6050_ReadAcc(IMU_MEASURE * measures){

	if(ACC_STATE == DISABLED) return;

	// Read data
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, rec_data1, 6, 500);

	// Parse data
	acc_X_raw = (int16_t)(rec_data1[0] << 8 | rec_data1[1]);
	acc_Y_raw = (int16_t)(rec_data1[2] << 8 | rec_data1[3]);
	acc_Z_raw = (int16_t)(rec_data1[4] << 8 | rec_data1[5]);

	// Scale data
	measures->acc_X = (double)acc_X_raw/ACC_SCALE_FACTOR;
	measures->acc_Y = (double)acc_Y_raw/ACC_SCALE_FACTOR;
	measures->acc_Z = (double)acc_Z_raw/ACC_SCALE_FACTOR;
}






void MPU6050_ReadGyro(IMU_MEASURE * MPU_measure){

	if(GYRO_STATE == DISABLED) return;

	// Read data
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, rec_data2, 6, 500);

	// Parse data
	gyro_X_raw = (int16_t)(rec_data2[0] << 8 | rec_data2[1]);
	gyro_Y_raw = (int16_t)(rec_data2[2] << 8 | rec_data2[3]);
	gyro_Z_raw = (int16_t)(rec_data2[4] << 8 | rec_data2[5]);

	// Scale data
	MPU_measure->gyro_X = (double)(gyro_X_raw/GYRO_SCALE_FACTOR);
	MPU_measure->gyro_Y = (double)(gyro_Y_raw/GYRO_SCALE_FACTOR);
	MPU_measure->gyro_Z = (double)(gyro_Z_raw/GYRO_SCALE_FACTOR);
}




void MPU6050_ElaborateData(IMU_MEASURE * measures){


	// State machine for the accelerometer
	if(ACC_STATE == CALIBRATION){

		measures->acc_angle_X = atan(measures->acc_X / measures->acc_Z) * RAD_TO_DEG;
		measures->acc_angle_Y = asin(measures->acc_X / GRAV_CONST) * RAD_TO_DEG;

	}



	// State machine for the gyroscope
	if(GYRO_STATE == CALIBRATION){
		iter_g += 1;

		// Cumulative sum for the average
		avrg_gX += gyro_X_scaled;
		avrg_gY += gyro_Y_scaled;
		avrg_gZ += gyro_Z_scaled;

		// Compute average
		if(iter_g == CALIBRATION_TIME*SAMPL_FREQ){
			avrg_gX = avrg_gX/iter_g;
			avrg_gY = avrg_gY/iter_g;
			avrg_gZ = avrg_gZ/iter_g;

			GYRO_STATE = READY;
			//PRINTF("MPU6050 READY TO USE - gyro \n\r");
		}

	}else if(GYRO_STATE == READY){

		// Manually the bias
		measures->gyro_X = measures->gyro_X-avrg_gX;
		measures->gyro_Y = measures->gyro_Y-avrg_gY;
		measures->gyro_Z = measures->gyro_Z-avrg_gZ;

		// Integrate
		measures->gyro_angle_X += measures->gyro_X/SAMPL_FREQ;
		measures->gyro_angle_Y += measures->gyro_Y/SAMPL_FREQ;
		measures->gyro_angle_Z += measures->gyro_Z/SAMPL_FREQ;
	}
}



void MPU6050_SensorFusion(IMU_MEASURE * measures){

	if(GYRO_STATE==READY && ACC_STATE==READY){

		measures->angle_X = measures->gyro_angle_X * 0.98 +  measures->acc_angle_X * 0.02;
		measures->angle_Y = measures->gyro_angle_Y * 0.98 +  measures->acc_angle_Y * 0.02;

	}
}




void MPU6050_ComplementFilter(IMU_MEASURE * measures){

	if(GYRO_STATE==READY && ACC_STATE==READY){


		// Get angle from accelerometer
		measures->acc_angle_X = atan(measures->acc_X / measures->acc_Z) * RAD_TO_DEG;
		measures->acc_angle_Y = asin(measures->acc_X / GRAV_CONST) * RAD_TO_DEG;

		// Get euler angles from gyroscope
		float roll_rate  = measures->gyro_Y + measures->gyro_X*sin(measures->angle_Y)*tan(measures->angle_X) + measures->gyro_Z*cos(measures->angle_Y)*tan(measures->angle_X);
		float pitch_rate = measures->gyro_X*cos(measures->angle_Y) - measures->gyro_Z*sin(measures->angle_Y);


		// Actual complementary filter
		measures->angle_X = measures->acc_angle_X*ALPHA_COMP + (1-ALPHA_COMP)*(measures->angle_X + pitch_rate/SAMPL_FREQ);
		measures->angle_Y = measures->acc_angle_Y*ALPHA_COMP + (1-ALPHA_COMP)*(measures->angle_Y + roll_rate/SAMPL_FREQ);
	}
}








