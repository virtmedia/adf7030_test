/*
 * adf7030.h
 *
 *  Created on: 4 cze 2017
 *      Author: Virtmedia
 */

#ifndef ADF7030_H_
#define ADF7030_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal.h"
/**
 * Hardware-specific functions
 */
void adf7030_rst_low(void);
void adf7030_rst_high(void);
void adf7030_cs_low(void);
void adf7030_cs_high(void);
uint8_t adf7030_spi_init(SPI_HandleTypeDef *hspi);
uint8_t adf7030_spi_byte(uint8_t dataToSend); //Without CS manipulation
void adf7030_delay_ms(uint32_t duration);


uint8_t adf7030_spi_byte_cs(uint8_t dataToSend);//With CS manipulation
void adf7030_begin(void);

#endif /* ADF7030_H_ */
