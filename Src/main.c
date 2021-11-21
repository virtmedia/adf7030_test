/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "i2c.h"
#include "iwdg.h"
#include "rtc.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h" // Plik bedacy interfejsem uzytkownika do kontrolera USB
#include "id.h"
#include "test.c"
#include "ssd1306.h"
#include "Adafruit_GFX.h"
#incude "adf7030.h"
//#include "adf7030.h"
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
/* Private variables ---------------------------------------------------------*/
const uint8_t logo_bitmap[] = { //Created in GIMP -> export to .xbm
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0xf0, 0x03, 0xfc, 0x1f, 0x00, 0xfc, 0xf0, 0xff, 0x81, 0x1f, 0xe0,
		   0x7f, 0x80, 0x1f, 0x00, 0x00, 0xfc, 0x0f, 0xfc, 0x7f, 0x00, 0xfe, 0xf1,
		   0xff, 0xe0, 0x7f, 0xe0, 0x3f, 0xe0, 0x7f, 0x00, 0x00, 0xfe, 0x1f, 0xfc,
		   0xff, 0x00, 0xff, 0xf3, 0xff, 0xf0, 0xff, 0xe0, 0x3f, 0xf0, 0xff, 0x00,
		   0x00, 0xfe, 0x1f, 0xfc, 0xff, 0x81, 0xff, 0xf1, 0xff, 0xf0, 0xff, 0xe0,
		   0x1f, 0xf0, 0xff, 0x00, 0x00, 0xff, 0x3f, 0xfc, 0xff, 0xc3, 0xff, 0xf0,
		   0x7f, 0xf8, 0xff, 0xe1, 0x1f, 0xf8, 0xff, 0x01, 0x00, 0x3f, 0x3e, 0x7c,
		   0xf0, 0xc3, 0x27, 0x00, 0x7c, 0xf8, 0xf0, 0x81, 0x0f, 0xf8, 0xf0, 0x01,
		   0x00, 0x1f, 0x3e, 0x7c, 0xe0, 0xc7, 0x07, 0x00, 0x7e, 0xf8, 0xf0, 0x81,
		   0x0f, 0xf8, 0xf0, 0x01, 0x00, 0x1f, 0x3e, 0x7c, 0xc0, 0xc7, 0x07, 0x00,
		   0x3e, 0xf8, 0xf0, 0xc1, 0x1f, 0xf8, 0xf0, 0x01, 0x00, 0x1f, 0x3e, 0x7c,
		   0xc0, 0xc7, 0x07, 0x00, 0x3e, 0xf8, 0xf0, 0xc1, 0x3f, 0xf8, 0xf0, 0x01,
		   0x00, 0x1f, 0x3e, 0x7c, 0xc0, 0xc7, 0x1f, 0x00, 0x3f, 0xf8, 0xf0, 0x01,
		   0x3e, 0xf8, 0xf0, 0x01, 0x00, 0x7f, 0x3e, 0x7c, 0xc0, 0xc7, 0x1f, 0x00,
		   0x3f, 0xf8, 0xf0, 0x01, 0x7c, 0xf8, 0xf0, 0x01, 0x00, 0x7f, 0x3e, 0x7c,
		   0xc0, 0xc7, 0x1f, 0x00, 0x1f, 0xf8, 0xf0, 0x01, 0x7c, 0xf8, 0xf0, 0x01,
		   0x00, 0x7f, 0x3e, 0x7c, 0xe0, 0xc7, 0x1f, 0x80, 0x1f, 0xf8, 0xf0, 0x01,
		   0x7c, 0xf8, 0xf0, 0x01, 0x00, 0x7f, 0x3e, 0x7c, 0xf0, 0xc3, 0x1f, 0x80,
		   0x1f, 0xf8, 0xf0, 0x21, 0x7e, 0xf8, 0xf0, 0x01, 0x00, 0x7f, 0x3e, 0x7c,
		   0xff, 0xc3, 0x07, 0x80, 0x0f, 0xf8, 0xff, 0xe1, 0x7f, 0xf8, 0xff, 0x01,
		   0x00, 0x1f, 0x3e, 0x7c, 0xff, 0xc1, 0x07, 0x80, 0x0f, 0xf0, 0xff, 0xe0,
		   0x3f, 0xf0, 0xff, 0x00, 0x00, 0x1f, 0x3e, 0x7c, 0xff, 0xc0, 0x07, 0xc0,
		   0x0f, 0xf0, 0xff, 0xe0, 0x3f, 0xf0, 0xff, 0x00, 0x00, 0x1f, 0x3e, 0x7c,
		   0x7f, 0xc0, 0x07, 0xc0, 0x0f, 0xe0, 0x7f, 0xe0, 0x1f, 0xe0, 0x7f, 0x00,
		   0x00, 0x1f, 0x3e, 0x7c, 0x1f, 0xc0, 0x07, 0xe0, 0x07, 0x80, 0x1f, 0xe0,
		   0x07, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0xe0, 0xff, 0x87, 0x7f, 0x80, 0xef, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xe7, 0x7f, 0xe0, 0xef, 0xff, 0x07,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xe7, 0x7f,
		   0xf0, 0xef, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0xe0, 0xff, 0xf7, 0x7f, 0xf0, 0xef, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xf7, 0x7f, 0xf8, 0xef, 0xff, 0x07,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x01,
		   0xf8, 0x03, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x3e, 0xf0, 0x01, 0xf8, 0x01, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x01, 0xf8, 0x01, 0x3e, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x7f,
		   0xf8, 0x03, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x3e, 0xf0, 0x7f, 0xf0, 0x07, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x7f, 0xe0, 0x07, 0x3e, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x7f,
		   0xe0, 0x0f, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x3e, 0xf0, 0x01, 0xc0, 0x0f, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x01, 0xe4, 0x0f, 0x3e, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xf0, 0x7f,
		   0xfc, 0x0f, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x3e, 0xf0, 0x7f, 0xfc, 0x07, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xe0, 0x7f, 0xfc, 0x07, 0x3e, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0xe0, 0x7f,
		   0xfc, 0x01, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x3e, 0x80, 0x7f, 0xfc, 0x00, 0x3e, 0x00, 0x00, 0xc7, 0x41, 0x3e,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x80, 0x28, 0x62, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x52, 0x10, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x42, 0x08,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x22, 0x42, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x42, 0x04, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xcf, 0x41, 0x04,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00 };
//Rejestry

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

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
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_CRC_Init();
  MX_IWDG_Init();
  MX_USB_DEVICE_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	//HAL_IWDG_Init(&hiwdg);
	//HAL_IWDG_Start(&hiwdg);
	//HAL_IWDG_Refresh(&hiwdg);
  	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	HAL_ADC_Start(&hadc1);
	begin();
	drawXBitmap(0,0,(uint8_t *)logo_bitmap,128,64,WHITE);
	display();
	for(int i=0;i<10;++i)
	{
		HAL_Delay(100);
		if(HAL_IWDG_Refresh(&hiwdg) != HAL_OK)
			{
			      /* Refresh Error */
			      Error_Handler();
			}
	}


	clearDisplay();
	display();
	Adafruit_GFX(getWidth(), getHeight());
	fillCircle(110, 52, 10, WHITE);
	setTextSize(1);
	//setTextColor1(WHITE);
	setTextColor2(WHITE, BLACK);
	setCursor(0,0);
	drawText("Test 5 FLASH: ");

	char strBuf[20];
	sprintf(strBuf,"%dKB",TM_ID_GetFlashSize());
	drawText(strBuf);

	setCursor(0,8);
	drawText("ID: ");
	sprintf(strBuf,"0x%lX%lX%lX",TM_ID_GetUnique32(0),TM_ID_GetUnique32(1),TM_ID_GetUnique32(2));
	drawText(strBuf);

	//setCursor(0,24);
	sprintf(strBuf,"  %ldMHz",HAL_RCC_GetSysClockFreq()/1000000);
		drawText(strBuf);
	display();
	int a =0;
	float temperature =0.0;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	char strBuf[20];
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	setCursor(0,24);
	RTC_TimeTypeDef currTime;
	HAL_RTC_GetTime(&hrtc,&currTime, RTC_FORMAT_BIN);
	sprintf(strBuf,"%02u:%02u:%02u",currTime.Hours,currTime.Minutes, currTime.Seconds );
	drawText(strBuf);


	if( HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK )
	{
		const float V25 = 1.35; // [Volts] 1.34 - 1.52
		const float Avg_slope = 4.3/1000.0; //[Volts/degree] 4.0 - 4.6
		const float SupplyVoltage = 3.3; // [Volts]
		const float ADCResolution = 4095.0;
		float Vadc = (SupplyVoltage*HAL_ADC_GetValue(&hadc1))/ADCResolution;
		temperature = ((V25-Vadc)/Avg_slope)+25;

		HAL_ADC_Start(&hadc1);
	}

	if(HAL_GPIO_ReadPin(USER_SW_GPIO_Port, USER_SW_Pin) == GPIO_PIN_RESET)
	{
		a=0;
		setCursor(0,40);
		drawText("        ");
		fillCircle(110, 52, 8, BLACK);
	}
	else
	{
		fillCircle(110, 52, 10, WHITE);
	}


	sprintf(strBuf,"%d",++a);
	setCursor(0,40);
	drawText(strBuf);
	//temperature on OLED; 0xF7 - char for the degree symbol, source: https://community.arduboy.com/t/a-small-program-to-display-the-font/145/3
	int MessageLength = sprintf(strBuf,"%2.4f%cC",temperature, 0xF7);
	setCursor(0,50);
	drawText(strBuf);
	//temperature on USB virtual COM
	MessageLength = sprintf(strBuf,"%g\r\n",temperature);
	CDC_Transmit_FS((uint8_t *)strBuf, MessageLength);
	display();

	if(HAL_IWDG_Refresh(&hiwdg) != HAL_OK)
	{
	      /* Refresh Error */
	      Error_Handler();
	}


	HAL_Delay(10);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
