#include "ESC_ctrl.h"
#include "tim.h"



char cmd_rx[1];


// FUNCTIONS *****************************

void ESC_setSpeed(int dutyCycle, ESC_STATUS * ESC_speed){

	TIM2->CCR1 = ESC_speed->FR + 1000;
	TIM2->CCR2 = ESC_speed->FL + 1000;


}

