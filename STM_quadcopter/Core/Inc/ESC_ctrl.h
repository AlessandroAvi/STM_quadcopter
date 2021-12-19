#include "main.h"
#include "tim.h"
#include "MPU6050.h"

#define PWM_1_MS 	1200
#define PWM_2_MS 	2400


typedef enum{
	DISARMED = 0,
	ARMED = 1
}ESC_STATE;



typedef struct{

	int16_t FR;
	int16_t FL;
	int16_t RR;
	int16_t RL;

	int16_t up_value;

	ESC_STATE state;

}ESC_CONF;




extern char cmd_rx[1];


void ESC_Init(ESC_CONF * ESC_speed);

void ESC_Calibrate(ESC_CONF * ESC_speed);

void ESC_followCmd(ESC_CONF * ESC_speed, IMU_MEASURE * MPU_measure,  char cmd);

void ESC_setSpeed(ESC_CONF * ESC_speed);

void CMD_transform(ESC_CONF * ESC_speed, char cmd);

