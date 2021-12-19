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

#define ACC_SCALE_FACTOR  	8192
#define GYRO_SCALE_FACTOR 	65.5



typedef enum{
	DISABLED = 0,
	CALIBRATION = 1,
	READY
}IMU_STATE;

typedef struct{
	double gyro_angle_X;
	double gyro_angle_Y;
	double gyro_angle_Z;

	double gyro_angle_dX;
	double gyro_angle_dY;
	double gyro_angle_dZ;

	double acc_angle_X;
	double acc_angle_Y;

	double angle_X;
	double angle_Y;
	double angle_Z;

}IMU_MEASURE;




// -------------------------------
// Accelerometer

uint8_t rec_data1[6];
uint16_t iter_a;

int16_t acc_X_raw, acc_Y_raw, acc_Z_raw;
double acc_X_scaled, acc_Y_scaled, acc_Z_scaled;
double avrg_aX, avrg_aY, avrg_aZ;
double tot_acc;

IMU_STATE ACC_STATE;

// -------------------------------
// Gyroscope

uint8_t rec_data2[6];
uint16_t iter_g;

int16_t gyro_X_raw, gyro_Y_raw, gyro_Z_raw;
double gyro_X_scaled, gyro_Y_scaled, gyro_Z_scaled;
double avrg_gX, avrg_gY, avrg_gZ;

IMU_STATE GYRO_STATE;




// -------------------------------
// FUNCTIONS

void MPU6050_Reset(IMU_MEASURE * MPU_measure);

void MPU6050_Init(IMU_MEASURE * MPU_measure);

void MPU6050_ReadAcc(IMU_MEASURE * MPU_measure);

void MPU6050_ReadGyro(IMU_MEASURE * MPU_measure);

void MPU6050_SensorFusion(IMU_MEASURE * MPU6050_measure);
