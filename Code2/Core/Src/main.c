/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void selectRow(uint8_t row);
uint8_t Keypad_Getkey();
void Press (uint8_t key);
void Release (uint8_t key);
void Keypad_handle();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define DEL 10
#define cong 11
#define tru 12
#define nhan 13
#define chia 14
#define bang 15
#define ko 16
float num[10] = {0,0,0,0,0,0,0,0,0,0}; //luu so
uint8_t equaltion[9] = {0,0,0,0,0,0,0,0,0}; // luu dau
uint8_t pos = 0; //vi tri
uint8_t key_current=0;
uint8_t key_last=0;
float kq=0;
int64_t num1=0;
uint8_t row=0;


const uint8_t key_code [8][2] =
{
		{7,8},
		{9,cong},
		{4,5},
		{6,tru},
		{1,2},
		{3,nhan},
		{ko,bang},
		{DEL,chia},
};

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
  /* USER CODE BEGIN 2 */
  LCD_Init();
  LCD_Write_String("BTL ESD Nhom 18");
  HAL_Delay(2000);
  LCD_Clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  key_current = Keypad_Getkey();
	  Keypad_handle();
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void selectRow(uint8_t row)
{
	switch (row){
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
	break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
		break;
	}
};
uint8_t Keypad_Getkey()
{
	for (row=0 ; row<8 ; row ++)
	{
		selectRow(row);
		HAL_Delay(2);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == 0)
			{
				HAL_Delay(50);
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == 0)
				return key_code[row][0];
			}
			else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == 0)
			{
				HAL_Delay(50);
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == 0)
				return key_code[row][1];
			}
	}
	return 0;
}
void Press (uint8_t key)
{
	if ((key==1) || (key==2) || (key==3) || (key==4) || (key==5) || (key==6) || (key==7) || (key==8) || (key==9) || (key==ko))
	{
		if (key==ko)
		{
			key=0;
	    }
			LCD_Write_Number(key);
	}
	if ((key==cong))
	{
		LCD_Write_String("+");
		equaltion[pos] = 1;
	}
	else if ((key==tru))
	{
		LCD_Write_String("-");
		equaltion[pos] = 2;
	}
	else if ((key==nhan))
	{
		LCD_Write_String("x");
		equaltion[pos] = 3;
	}
	else if ((key==chia))
	{
		LCD_Write_String(":");
		equaltion[pos] = 4;
	}
	if (key==bang)
	{
		num[pos] = num1;
		for(uint8_t i = 0; i < 9; i++)
		{
			if (equaltion[i] == 3)
			{
				num[i+1] = num[i] * num[i+1];
				num[i] = 0;
				if (i>0)
				{
					equaltion[i] = equaltion[i-1];
				}
				else equaltion[i] = 1;
			}
			else if (equaltion[i] == 4)
			{
				num[i+1] = num[i] / num[i+1];
				num[i] = 0;
				if (i>0)
				{
					equaltion[i] = equaltion[i-1];
				}
				else equaltion[i] = 1;
			}
		}
		for(uint8_t i = 0; i < 10; i++)
		{
			if (equaltion[i] == 1)
			{
				num[i+1] = num[i] + num[i+1];
			}
			else if (equaltion[i] == 2)
			{
				num[i+1] = num[i] - num[i+1];
			}
			else if (equaltion[i] == 0) {
				kq = num[i];
				break;
			}

		}
		LCD_Location(1, 0);
		LCD_Write_Float(kq);
	}
	if (key==DEL)
	{
		LCD_Clear();
		LCD_Location(0, 0);
	}
}
void Release (uint8_t key)
{
	  if ((key==1) || (key==2) || (key==3) || (key==4) || (key==5) || (key==6) || (key==7) || (key==8) || (key==9) || (key==ko))
	  {
		  if (key==ko)
		  {
			  key=0;
		  }
	 	  num1 = num1*10 + key;
	  }
	  if ((key==cong) || (key==tru) || (key==nhan) || (key==chia))
	  {
		  num[pos] = num1;
		  num1 = 0; //reset num1
		  pos++;
	  }
	  if (key==bang)
	  {

	  }
	  if (key==DEL)
	  {
		  num1=0;
		  pos=0;
		  for (uint8_t i = 0; i < 9; i++) {
		      equaltion[i] = 0;
		  }
		  for (uint8_t i = 0; i < 10; i++) {
		      num[i] = 0;
		  }
	  }
}
void Keypad_handle()
{
	if ( key_current != key_last )
	{
		if ( key_current !=0 ) Press(key_current);
		else Release (key_last);
		key_last = key_current;
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
