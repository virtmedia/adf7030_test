/*
 * adf7030.c
 *
 *  Created on: 4 cze 2017
 *      Author: Virtmedia
 */
#include "adf7030.h"
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal.h"
//#include "Adafruit_GFX.h"

#define SSD1306_ADDR (0x78)

extern SPI_HandleTypeDef hspi1;

void adf7030_begin(void)
{
	HAL_GPIO_WritePin(ADF_RST_GPIO_Port,ADF_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(ADF_RST_GPIO_Port,ADF_RST_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(
	HAL_SPI_Init(&hspi1);
}
