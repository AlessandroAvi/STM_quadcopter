#include "main.h"
#include "tim.h"



typedef enum{
	FAN_FR = 0,
	FAN_FL,
	FAN_RR,
	FAN_RL
}ESC_POS;



void ESC_setSpeed(int dutyCycle, ESC_POS fan);

void ESC_initialSetUp();
