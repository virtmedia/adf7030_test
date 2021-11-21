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
#include "gpio.h"
//#include "Adafruit_GFX.h"

#define SSD1306_ADDR (0x78)

/**
 * Hardware-specific functions
 */

extern SPI_HandleTypeDef hspi1;

void adf7030_rst_low(void)
{
	HAL_GPIO_WritePin(ADF_RST_GPIO_Port,ADF_RST_Pin, GPIO_PIN_RESET);
}

void adf7030_rst_high(void)
{
	HAL_GPIO_WritePin(ADF_RST_GPIO_Port,ADF_RST_Pin, GPIO_PIN_SET);
}

void adf7030_cs_low(void)
{
	HAL_GPIO_WritePin(ADF_RST_GPIO_Port,ADF_CS_Pin, GPIO_PIN_RESET);
}

void adf7030_cs_high(void)
{
	HAL_GPIO_WritePin(ADF_RST_GPIO_Port,ADF_CS_Pin, GPIO_PIN_SET);
}

uint8_t adf7030_spi_init(SPI_HandleTypeDef *hspi)
{
	HAL_SPI_Init(&hspi1);

	return 0; //initialization failed
}

uint8_t adf7030_spi_byte(uint8_t dataToSend) //Without CS manipulation
{
	uint8_t dataReceived;
	HAL_SPI_TransmitReceive(&hspi1,&dataToSend, &dataReceived, 1, 255);
	return dataReceived;
}

void adf7030_delay_ms(uint32_t duration)
{
	HAL_Delay(duration);
}

/**
 * Main functions
 */
uint8_t adf7030_spi_byte_cs(uint8_t dataToSend)//With CS manipulation
{
	uint8_t dataReceived;
	adf7030_cs_low();
	dataReceived = adf7030_spi_byte(dataToSend);
	adf7030_cs_high();
	return dataReceived;
}

void adf7030_begin(void)
{
	adf7030_spi_init(&hspi1);
	adf7030_rst_low();
	adf7030_delay_ms(1);
	adf7030_rst_high();

}
