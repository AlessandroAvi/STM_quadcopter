#include "ESC_ctrl.h"
#include "tim.h"



char cmd_rx[1];


// FUNCTIONS *****************************

void ESC_setSpeed(int dutyCycle, ESC_STATUS * ESC_speed){

	TIM2->CCR1 = ESC_speed->FR + 1000;
	TIM2->CCR2 = ESC_speed->FL + 1000;


}




void CMD_transform(ESC_STATUS * ESC_speed, char cmd){


	if(cmd == 'W'){	// forward

	}else if(cmd == 'A'){ // left
		ESC_speed.FR += 1;
		ESC_speed.FL -= 1;

	}else if(cmd == 'S'){ // back

	}else if(cmd == 'D'){ // right
		ESC_speed.FR -= 1;
		ESC_speed.FL += 1;

	}else if(cmd == 'I'){ // up
		ESC_speed.FR += 1;
		ESC_speed.FL += 1;

	}else if(cmd == 'J'){ // rotate left

	}else if(cmd == 'K'){ // down
		ESC_speed.FR -= 1;
		ESC_speed.FL -= 1;

	}else if(cmd == 'L'){ // rotate right

	}else if(cmd == 'X'){ // ?

	}else if(cmd == 'C'){ // ?

	}

}
