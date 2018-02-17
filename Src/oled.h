/*
 * oled.h
 *
 *  Created on: 3 cze 2017
 *      Author: Virtmedia
 */

#ifndef OLED_H_
#define OLED_H_



void OLED_Init(void);
HAL_StatusTypeDef OLED_Cmd(uint8_t data);
HAL_StatusTypeDef OLED_Data(uint8_t data);
void SetPosChar(uint8_t x, uint8_t y);
void SetPos(uint8_t x, uint8_t y);
void CharMedium(uint8_t cyfra, uint8_t x,uint8_t y );
void CharBig(uint8_t cyfra, uint8_t x,uint8_t y );
void WriteChar(char code);
void OledTxt(const char *napis,char x,char y);
uint8_t SetColumn(uint8_t column);
uint8_t SetLine(uint8_t line);
uint8_t SetPage(uint8_t page);
void OledBmp(void);
void OledCls(void);







#endif /* OLED_H_ */
