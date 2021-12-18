#include "main.h"
#include "i2c.h"
#include "debug.h"
#include "string.h"
#include "stdio.h"
#include <math.h>

// -------------------------------
// I2C REGISTER ADDRESSES -----

#define MPU6050_ADDR 		0X68 << 1
#define SMPLRT_DIV_REG 		0X19		// where sample rate is stored
#define CONFIG				0X1A		// where digital low pass filter config is stored
#define GYRO_CONFIG_REG 	0X1B
#define ACCEL_CONFIG_REG 	0X1C

// Register where accelerometer data is stored
#define ACCEL_XOUT_H_REG 	0X3B
#define ACCEL_XOUT_L_REG 	0X3C
#define ACCEL_YOUT_H_REG 	0X3D
#define ACCEL_YOUT_L_REG 	0X3E
#define ACCEL_ZOUT_H_REG 	0X3F
#define ACCEL_ZOUT_L_REG 	0X40

#define TEMP_OUT_H_REG 		0X41

// Register where gyroscope data is stored
#define GYRO_XOUT_H_REG 	0X43
#define GYRO_XOUT_L_REG 	0X44
#define GYRO_YOUT_H_REG 	0X45
#define GYRO_YOUT_L_REG 	0X46
#define GYRO_ZOUT_H_REG 	0X47
#define GYRO_ZOUT_L_REG 	0X48

#define PWR_MGMT_1_REG 		0x6B
#define WHO_AM_I_REG 		0x75






// -------------------------------
// IMU PARAMETERS


#define CALIBRATION_TIME  	2
#define SAMPL_FREQ 			250
#define PI 					3.14159265
#define DEG_TO_RAD 			PI/180
#define RAD_TO_DEG 			180/PI

typedef enum{
	DISABLED = 0,
	CALIBRATION = 1,
	READY
}IMU_STATE;

typedef struct{
	double angle_X;
	double angle_Y;
	double angle_Z;

	double angle_dX;
	double angle_dY;
	double angle_dZ;

	double acc_X;
	double acc_Y;
	double acc_Z;

}IMU_MEASURE;

int millis;
uint16_t iter;


// -------------------------------
// Accelerometer

uint8_t rec_data1[6];

int16_t acc_X_raw, acc_Y_raw, acc_Z_raw;
double acc_X, acc_Y, acc_Z;
int ACC_SCALE_FACTOR;


// -------------------------------
// Gyroscope

uint8_t rec_data2[6];

int16_t gyro_X_raw, gyro_Y_raw, gyro_Z_raw;
double gyro_X_scaled, gyro_Y_scaled, gyro_Z_scaled;
double avrg_gX, avrg_gY, avrg_gZ;
double GYRO_SCALE_FACTOR;






// -------------------------------
// FUNCTIONS

void MPU6050_Init(IMU_MEASURE * MPU_measure);

void MPU6050_ReadAcc(IMU_MEASURE * MPU_measure);

void MPU6050_ReadGyro(IMU_MEASURE * MPU_measure);
