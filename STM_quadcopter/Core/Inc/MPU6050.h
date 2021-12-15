#include "main.h"
#include "i2c.h"
#include "debug.h"
#include "string.h"
#include "stdio.h"


// I2C REGISTER ADDRESSES

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



#define REC_SIZE			2
#define SAMPL_FREQ 			250

uint8_t MPU_STATE;

int16_t acc_X_raw;
int16_t acc_Y_raw;
int16_t acc_Z_raw;

int16_t gyro_X_raw;
int16_t gyro_Y_raw;
int16_t gyro_Z_raw;

uint8_t rec_data1[6];
uint8_t rec_data2[6];

double ax, ay, az;

double gyro_X_scaled, gyro_Y_scaled, gyro_Z_scaled;
double avrg_gX, avrg_gY, avrg_gZ;
double angle_x, angle_y, angle_z;



int millis;





//double arr_gx[REC_SIZE*SAMPL_FREQ], arr_gy[REC_SIZE*SAMPL_FREQ], arr_gz[REC_SIZE*SAMPL_FREQ];
int arr_time[REC_SIZE*SAMPL_FREQ];
uint16_t iter;
int STOP_REC_FLAG;

// Debug message
char debug_gyro[100];
char debug_acc[100];


// fUNCTIONS
void MPU6050_Init();
void MPU6050_ReadAcc(void);
void MPU6050_ReadGyro(void);
