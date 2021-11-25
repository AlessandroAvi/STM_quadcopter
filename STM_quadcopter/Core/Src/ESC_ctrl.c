#include "ESC_ctrl.h"
#include "tim.h"





void ESC_setSpeed(int dutyCycle, ESC_POS fan){

	if(fan==FAN_FR){
		TIM2->CCR1 = dutyCycle + 100;
	}else if(fan==FAN_FL){
		TIM2->CCR2 = dutyCycle+100;
	}else if(fan==FAN_RR){
		TIM2->CCR1 = dutyCycle + 100;
	}else if(fan==FAN_RL){
		TIM2->CCR1 = dutyCycle + 100;
	}

}

