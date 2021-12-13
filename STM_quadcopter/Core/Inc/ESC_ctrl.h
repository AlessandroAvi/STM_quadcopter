#include "main.h"
#include "tim.h"


typedef struct{

	uint16_t FR;
	uint16_t FL;
	uint16_t RR;
	uint16_t RL;

}ESC_STATUS;



extern char cmd_rx[1];




void ESC_setSpeed(ESC_STATUS * ESC_speed, double gx, double gy, double gz);

void CMD_transform(ESC_STATUS * ESC_speed, char cmd);

void ESC_initialSetUp();
