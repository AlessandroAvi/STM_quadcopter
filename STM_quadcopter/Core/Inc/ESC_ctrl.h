#include "main.h"
#include "tim.h"
#include "MPU6050.h"


typedef enum{
	DISARMED = 0,
	ARMED = 1
}ESC_STATE;



typedef struct{

	uint16_t FR;
	uint16_t FL;
	uint16_t RR;
	uint16_t RL;

	ESC_STATE state;

}ESC_CONF;




extern char cmd_rx[1];


void ESC_Init(ESC_CONF * ESC_speed);

void ESC_followCmd(ESC_CONF * ESC_speed, IMU_MEASURE * MPU_measure,  char cmd);

void ESC_setSpeed(ESC_CONF * ESC_speed);

void CMD_transform(ESC_CONF * ESC_speed, char cmd);

