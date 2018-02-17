/*
 * id.h
 *
 *  Created on: 4 cze 2017
 *      Author: Virtmedia
 */

#ifndef ID_H_
#define ID_H_

#if defined(STM32F103xB)
#define ID_UNIQUE_ADDRESS        0x1FFFF7E8 /*!< STM32F0xx address */
#endif
#if defined(STM32F103xB)
#define ID_FLASH_ADDRESS         0x1FFFF7E0 /*!< STM32F0xx address */
#endif

/**
 * @brief  Gets STM32Fxxx device flash size in kilo bytes
 * @note   Defined as macro to get maximal response time
 * @param  None
 * @retval Flash size in kilo bytes
 */
#define TM_ID_GetFlashSize()     (*(__IO uint16_t *) (ID_FLASH_ADDRESS))

/**
 * @brief  Gets STM32Fxxx unique ID number in 8-bit format
 * @note   STM32Fxxx has 96bits long unique ID, so 12 bytes are available for read in 8-bit format
 * @note   Defined as macro to get maximal response time
 * @param  x: Byte number: specify which part of 8 bits you want to read
 *               - Values between 0 and 11 are allowed
 * @retval Unique ID address
 */
#define TM_ID_GetUnique8(x)      ((x >= 0 && x < 12) ? (*(__IO uint8_t *) (ID_UNIQUE_ADDRESS + (x))) : 0)

/**
 * @brief  Gets unique ID number in 16-bit format
 * @note   STM32Fxxx has 96bits long unique ID, so 6 2-bytes values are available for read in 16-bit format
 * @note   Defined as macro to get maximal response time
 * @param  x: Byte number: specify which part of 16 bits you want to read
 *               - Values between 0 and 5 are allowed
 * @retval Unique ID address
 */
#define TM_ID_GetUnique16(x)     ((x >= 0 && x < 6) ? (*(__IO uint16_t *) (ID_UNIQUE_ADDRESS + 2 * (x))) : 0)

/**
 * @brief  Get unique ID number in 32-bit format
 * @note   STM32Fxxx has 96bits long unique ID, so 3 4-bytes values are available for read in 32-bit format
 * @note   Defined as macro to get maximal response time
 * @param  x: Byte number: specify which part of 32 bits you want to read
 *               - Values between 0 and 2 are allowed
 * @retval Unique ID address
 */
#define TM_ID_GetUnique32(x)     ((x >= 0 && x < 3) ? (*(__IO uint32_t *) (ID_UNIQUE_ADDRESS + 4 * (x))) : 0)


#endif /* ID_H_ */
