/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>

// My libraries
#include "ESC_ctrl.h"
#include "debug.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RX_MSG_LEN 3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// DEBUG MESSAGES

// RECEIVE INFO MESSAGE
uint8_t msgRx[RX_MSG_LEN];

//Define flags
int BLUE_BUTTON = 0;
int BLUETOOTH_FLAG = 0;

// CONTAINERS
int dutyCycle = 0;
int dummy=0;

IMU_MEASURE MPU_measure;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */

  PRINTF("\n\r BEGINNING OF THE CODE \n\n\r");

  // Start timer interrupt that enables the GYRO reading 250 Hz
  HAL_TIM_Base_Start_IT(&htim10);

  // Start timer for the PWM signal
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

  // Start interrupt for bluetooth Rx commands
  HAL_UART_Receive_IT(&huart6, (uint8_t*)cmd_rx, 1);

  ESC_CONF ESC_speed;

  ESC_Calibrate(&ESC_speed);

  PRINTF(" -- Press blue button to start the code \n\n\r");
  while(BLUE_BUTTON==0){
	  if(BLUE_BUTTON==1){
		  break;
	  }
  }

  MPU6050_Init(&MPU_measure);
  MPU6050_Reset(&MPU_measure);

  ESC_Init(&ESC_speed);





  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if(ACC_STATE == READY && GYRO_STATE == READY){
		  char messaggio[100];
		  int lengh = sprintf(messaggio, "ACC: x %f, y %f \n\r", MPU_measure.angle_X, MPU_measure.angle_Y);
		  HAL_UART_Transmit(&huart2, (uint8_t*)messaggio, lengh, 50);
	  }


	  // Receive the command from the radio/bl controller
	  if(BLUETOOTH_FLAG == 1){

		  //msgLen = sprintf(msgDebug, "\n\r   FRONTT LEFT %d  -  FRONT RIGHT %d  -  REAR LEFT %d - REAR RIGHT %d \r\n", ESC_speed.FL, ESC_speed.FR, ESC_speed.RL, ESC_speed.RR);
		  //HAL_UART_Transmit(&huart2, (uint8_t*)msgDebug, msgLen, 10);

		  BLUETOOTH_FLAG = 0;
	  }else{
		  cmd_rx[0] = ' ';
	  }

	  ESC_followCmd(&ESC_speed, &MPU_measure, cmd_rx[0]);
	  ESC_setSpeed(&ESC_speed);

	  //msgLen = sprintf(msgDebug, "\r FRONTT LEFT %d  -  FRONT RIGHT %d  -  REAR LEFT %d - REAR RIGHT %d", ESC_speed.FL, ESC_speed.FR, ESC_speed.RL, ESC_speed.RR);
	  //HAL_UART_Transmit(&huart2, (uint8_t*)msgDebug, msgLen, 10);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



// Interrupt from the timer
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim == &htim10){
		MPU6050_ReadAcc(&MPU_measure);
		MPU6050_ReadGyro(&MPU_measure);
		MPU6050_SensorFusion(&MPU_measure);
	}
}


// Interrupt from bluetooth
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart){

	if(BLUETOOTH_FLAG==0){
		BLUETOOTH_FLAG = 1;
	}

	HAL_UART_Receive_IT(&huart6, (uint8_t*)cmd_rx, 1);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin == B1_Pin){
		if(BLUE_BUTTON == 0){
			BLUE_BUTTON=1;
		}
	}

}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
