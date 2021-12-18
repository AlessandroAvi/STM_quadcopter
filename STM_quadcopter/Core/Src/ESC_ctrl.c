#include "ESC_ctrl.h"
#include "tim.h"



char cmd_rx[1];


// FUNCTIONS *****************************
void ESC_Init(ESC_CONF * ESC_speed){

	  ESC_speed->FR = 0;
	  ESC_speed->FL = 0;
	  ESC_speed->RR = 0;
	  ESC_speed->RL = 0;

	  ESC_speed->state = ARMED;

	  // Set PWM to 0 for the ESC (1 ms)
	  TIM3->CCR1 = ESC_speed->FR + 1000;
	  TIM3->CCR2 = ESC_speed->FL + 1000;
	  TIM3->CCR3 = ESC_speed->RR + 1000;
	  TIM3->CCR4 = ESC_speed->RL + 1000;
}


void ESC_followCmd(ESC_CONF * ESC_speed, IMU_MEASURE * MPU_measure, char cmd){

	int dummy = 0;
	int cmd_pitch = 0;
	int cmd_roll  = 0;
	int cmd_up    = 0;

	// PID values
	int P_pitch = 2;
	int D_pitch  = 1;
	//int I_pitch = 0;
	int P_roll  = 2;
	int D_roll  = 1;
	//int I_roll = 0;


	if(cmd == 'W'){	// forward
		cmd_pitch = -10;

	}else if(cmd == 'A'){ // left
		cmd_roll = -10;

	}else if(cmd == 'S'){ // back
		cmd_pitch = 10;

	}else if(cmd == 'D'){ // right
		cmd_roll = +10;

	}else if(cmd == 'I'){ // up
		cmd_up = 50;

	}else if(cmd == 'J'){ // rotate left
		dummy = 0;

	}else if(cmd == 'K'){ // down
		cmd_up = -50;

	}else if(cmd == 'L'){ // rotate right
		dummy = 0;

	}else if(cmd == 'X'){ // disarm drone
		ESC_speed->state = DISARMED;

	}else if(cmd == 'C'){ // arms DRONE
		ESC_speed->state = ARMED;

	}

	if(ESC_speed->state == ARMED){

		double pitch_err   = cmd_pitch - MPU_measure->angle_X;
		double pitch_d_err = MPU_measure->angle_dX;

		double roll_err    = cmd_roll  - MPU_measure->angle_Y;
		double roll_d_err  = MPU_measure->angle_dY;

		// DA PROVARE NON SONO SICURO
		ESC_speed->FR = cmd_up + pitch_err*P_pitch - pitch_d_err*D_pitch - roll_err*P_roll + roll_d_err*D_roll;
		ESC_speed->FL = cmd_up + pitch_err*P_pitch - pitch_d_err*D_pitch + roll_err*P_roll - roll_d_err*D_roll;
		ESC_speed->RR = cmd_up - pitch_err*P_pitch + pitch_d_err*D_pitch - roll_err*P_roll + roll_d_err*D_roll;
		ESC_speed->RL = cmd_up - pitch_err*P_pitch + pitch_d_err*D_pitch + roll_err*P_roll - roll_d_err*D_roll;

	}else if(ESC_speed->state == DISARMED){

		ESC_speed->FR = 0;
		ESC_speed->FL = 0;
		ESC_speed->RR = 0;
		ESC_speed->RL = 0;
	}
}


void ESC_setSpeed(ESC_CONF * ESC_speed){

	int top_lim = 600;
	int low_lim = 0;


	if(ESC_speed->FL > top_lim){
	  ESC_speed->FL = top_lim;
	}else if(ESC_speed->FL <= low_lim){
	  ESC_speed->FL = low_lim;
	}

	if(ESC_speed->FR > top_lim){
	  ESC_speed->FR = top_lim;
	}else if(ESC_speed->FR <= low_lim){
	  ESC_speed->FR = low_lim;
	}

	if(ESC_speed->RR > top_lim){
	  ESC_speed->RR = top_lim;
	}else if(ESC_speed->RR <= low_lim){
	  ESC_speed->RR = low_lim;
	}

	if(ESC_speed->RL > top_lim){
	  ESC_speed->RL = top_lim;
	}else if(ESC_speed->RL <= low_lim){
	  ESC_speed->RL = low_lim;
	}

	TIM3->CCR1 = ESC_speed->FR + 1000;
	TIM3->CCR2 = ESC_speed->FL + 1000;
	TIM3->CCR3 = ESC_speed->RR + 1000;
	TIM3->CCR4 = ESC_speed->RL + 1000;
}




void CMD_transform(ESC_CONF * ESC_speed, char cmd){

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
