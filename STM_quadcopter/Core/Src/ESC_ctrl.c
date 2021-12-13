#include "ESC_ctrl.h"
#include "tim.h"



char cmd_rx[1];


// FUNCTIONS *****************************

void ESC_setSpeed(ESC_STATUS * ESC_speed, double gx, double gy, double gz){

	  if(ESC_speed->FL > 1000){
		  ESC_speed->FL = 1000;
	  }else if(ESC_speed->FL <= 0 || ESC_speed->FL > 1000){
		  ESC_speed->FL = 0;
	  }

	  if(ESC_speed->FR > 1000){
		  ESC_speed->FR = 1000;
	  }else if(ESC_speed->FR <= 0 || ESC_speed->FR >1000){
		  ESC_speed->FR = 0;
	  }

	  if(ESC_speed->RR > 1000){
		  ESC_speed->RR = 1000;
	  }else if(ESC_speed->RR <= 0 || ESC_speed->RR >1000){
		  ESC_speed->RR = 0;
	  }

	  if(ESC_speed->RL > 1000){
		  ESC_speed->RL = 1000;
	  }else if(ESC_speed->RL <= 0 || ESC_speed->RL >1000){
		  ESC_speed->RL = 0;
	  }


	double variation = gx*10;

	TIM3->CCR1 = ESC_speed->FR + 1000 + variation;
	TIM3->CCR2 = ESC_speed->FL + 1000 - variation;
	TIM3->CCR3 = ESC_speed->RR + 1000;
	TIM3->CCR4 = ESC_speed->RL + 1000;
}




void CMD_transform(ESC_STATUS * ESC_speed, char cmd){

	int deltaFR = 0;
	int deltaFL = 0;
	int deltaRR = 0;
	int deltaRL = 0;
	int dummy = 0;
	int delta = 10;

	if(cmd == 'W'){	// forward
		deltaFR -= delta;
		deltaFL -= delta;
		deltaRR += delta;
		deltaRL += delta;

	}else if(cmd == 'A'){ // left
		deltaFR += delta;
		deltaFL -= delta;
		deltaRR += delta;
		deltaRL -= delta;

	}else if(cmd == 'S'){ // back
		deltaFR += delta;
		deltaFL += delta;
		deltaRR -= delta;
		deltaRL -= delta;

	}else if(cmd == 'D'){ // right
		deltaFR -= delta;
		deltaFL += delta;
		deltaRR -= delta;
		deltaRL += delta;

	}else if(cmd == 'I'){ // up
		deltaFR += delta;
		deltaFL += delta;
		deltaRR += delta;
		deltaRL += delta;

	}else if(cmd == 'J'){ // rotate left
		deltaFR += delta;
		deltaFL -= delta;
		deltaRR -= delta;
		deltaRL += delta;

	}else if(cmd == 'K'){ // down
		deltaFR -= delta;
		deltaFL -= delta;
		deltaRR -= delta;
		deltaRL -= delta;

	}else if(cmd == 'L'){ // rotate right
		deltaFR -= delta;
		deltaFL += delta;
		deltaRR += delta;
		deltaRL -= delta;

	}else if(cmd == 'X'){ // ?
		ESC_speed->FR = 0;
		ESC_speed->FL = 0;
		ESC_speed->RR = 0;
		ESC_speed->RL = 0;
		return;

	}else if(cmd == 'C'){ // ?

	}

	if(ESC_speed->FR==0 && deltaFR<0){
		dummy = 0;
	}else{
		ESC_speed->FR += deltaFR;
	}
	if(ESC_speed->FL==0 && deltaFL<0){
		dummy = 0;
	}else{
		ESC_speed->FL += deltaFL;
	}
	if(ESC_speed->RR==0 && deltaRR<0){
		dummy = 0;
	}else{
		ESC_speed->RR += deltaRR;
	}
	if(ESC_speed->RL==0 && deltaRL<0){
		dummy = 0;
	}else{
		ESC_speed->RL += deltaRL;
	}


}
