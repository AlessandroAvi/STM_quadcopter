#include "main.h"
#include "i2c.h"
#include "debug.h"
#include "string.h"
#include "stdio.h"


// DRESSED FOR THE GYRO DEVICE

#define MPU6050_ADDR 		0XD0
#define SMPLRT_DIV_REG 		0X19
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

int16_t acc_X_raw;
int16_t acc_Y_raw;
int16_t acc_Z_raw;

int16_t gyro_X_raw;
int16_t gyro_Y_raw;
int16_t gyro_Z_raw;

int8_t rec_data1[6];
int8_t rec_data2[6];

double ax, ay, az, gx, gy, gz;


// Debug message
char debug_gyro[100];
char debug_acc[100];


// fUNCTIONS
void MPU6050_Init();
void MPU6050_ReadAcc(void);
void MPU6050_ReadGyro(void);
