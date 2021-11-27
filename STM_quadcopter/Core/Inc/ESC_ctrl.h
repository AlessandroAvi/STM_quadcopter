#include "main.h"
#include "tim.h"


typedef struct{

	uint16_t FR;
	uint16_t FL;
	uint16_t RR;
	uint16_t RL;

}ESC_STATUS;



extern char cmd_rx[1];




void ESC_setSpeed(int dutyCycle, ESC_STATUS * ESC_speed);

void ESC_initialSetUp();
