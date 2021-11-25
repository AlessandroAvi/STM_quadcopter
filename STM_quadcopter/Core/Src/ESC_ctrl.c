#include "ESC_ctrl.h"






void ESC_setPWM(int dutyCycle){

	TIM2->CCR1 = dutyCycle+100;

}




void ESC_initialSetUp(){

	ESC_setPWM(100);

	HAL_Delay(4000);

	ESC_setPWM(0);


}
