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

	  ESC_speed->up_value = 0;

	  // Set PWM to 0 for the ESC (1 ms)
	  TIM3->CCR1 = ESC_speed->FR + PWM_1_MS;
	  TIM3->CCR2 = ESC_speed->FL + PWM_1_MS;
	  TIM3->CCR3 = ESC_speed->RR + PWM_1_MS;
	  TIM3->CCR4 = ESC_speed->RL + PWM_1_MS;
}

void ESC_Calibrate(ESC_CONF * ESC_speed){

	  TIM3->CCR1 = PWM_2_MS;
	  TIM3->CCR2 = PWM_2_MS;
	  TIM3->CCR3 = PWM_2_MS;
	  TIM3->CCR4 = PWM_2_MS;

	  ESC_speed->state = DISARMED;
}


void ESC_followCmd(ESC_CONF * ESC_speed, IMU_MEASURE * MPU_measure, char cmd){

	int cmd_pitch = 0;
	int cmd_roll  = 0;

	int16_t low_lim = 0;
	int16_t high_lim = 600;

	// PID values
	int P_pitch = 2;
	int D_pitch  = 1;
	//int I_pitch = 0;
	int P_roll  = 2;
	int D_roll  = 1;
	//int I_roll = 0;


	if(cmd == 'W'){	// forward
		cmd_pitch = -10;
		PRINTF(" FORWARD \n\r");


	}else if(cmd == 'A'){ // left
		cmd_roll = -10;
		PRINTF(" LEFT \n\r");


	}else if(cmd == 'S'){ // back
		cmd_pitch = 10;
		PRINTF(" BACK \n\r");


	}else if(cmd == 'D'){ // right
		cmd_roll = +10;
		PRINTF(" RIGHT \n\r");


	}else if(cmd == 'I'){ // up
		ESC_speed->up_value += 50;
		PRINTF(" UP \n\r");


	}else if(cmd == 'J'){ // rotate left
		PRINTF(" ROT LEFT \n\r");


	}else if(cmd == 'K'){ // down
		ESC_speed->up_value -= 50;
		PRINTF(" DOWN \n\r");

	}else if(cmd == 'L'){ // rotate right
		PRINTF(" ROT RIGHT \n\r");


	}else if(cmd == 'X'){ // disarm drone
		ESC_speed->state = DISARMED;
		PRINTF(" DISARM \n\r");


	}else if(cmd == 'C'){ // arms DRONE
		ESC_speed->state = ARMED;
		PRINTF(" ARM \n\r");


	}

	if(ESC_speed->state == ARMED){

		double pitch_err   = 0;//cmd_pitch - MPU_measure->angle_X;
		double pitch_d_err = 0;//MPU_measure->gyro_angle_dX;

		double roll_err    = 0;//cmd_roll  - MPU_measure->angle_Y;
		double roll_d_err  = 0;//MPU_measure->gyro_angle_dY;

		int16_t FR_tmp = ESC_speed->up_value + pitch_err*P_pitch - pitch_d_err*D_pitch - roll_err*P_roll + roll_d_err*D_roll;
		int16_t FL_tmp = ESC_speed->up_value + pitch_err*P_pitch - pitch_d_err*D_pitch + roll_err*P_roll - roll_d_err*D_roll;
		int16_t RR_tmp = ESC_speed->up_value - pitch_err*P_pitch + pitch_d_err*D_pitch - roll_err*P_roll + roll_d_err*D_roll;
		int16_t RL_tmp = ESC_speed->up_value - pitch_err*P_pitch + pitch_d_err*D_pitch + roll_err*P_roll - roll_d_err*D_roll;

		if(FR_tmp > low_lim && FR_tmp < high_lim){
			ESC_speed->FR = FR_tmp;
		}

		if(FL_tmp > low_lim && FL_tmp < high_lim){
			ESC_speed->FL = FL_tmp;
		}

		if(RR_tmp > low_lim && RR_tmp < high_lim){
			ESC_speed->RR = RR_tmp;
		}

		if(RL_tmp > low_lim && RL_tmp < high_lim){
			ESC_speed->RL = RL_tmp;
		}

	}else if(ESC_speed->state == DISARMED){

		ESC_speed->FR = 0;
		ESC_speed->FL = 0;
		ESC_speed->RR = 0;
		ESC_speed->RL = 0;
		ESC_speed->up_value =0;
	}
}


void ESC_setSpeed(ESC_CONF * ESC_speed){

	TIM3->CCR1 = ESC_speed->FR + PWM_1_MS;
	TIM3->CCR2 = ESC_speed->FL + PWM_1_MS;
	TIM3->CCR3 = ESC_speed->RR + PWM_1_MS;
	TIM3->CCR4 = ESC_speed->RL + PWM_1_MS;
}




