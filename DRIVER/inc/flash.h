/**
 * @file flash.h
 * @author Adelaide (1479398604xz@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) github:Adelai-lab 2023
 * 
 */
#ifndef __FLASH_H__
#define __FLASH_H__
#include "stm32f10x.h"

enum w25q64_cmd{
	WRITE_STATUS_REG    = 0x01,
	PAGE_PROGRAM        = 0x02,
	WRITE_DISABLE       = 0x04,
	READ_STATUS_REG1    = 0x05,
	WRITE_ENABLE		= 0x06,
	SECTOR_ERASE        = 0x20,
#if defined(USE_OF_32K)
	BLOCK_ERASE         = 0x52,
#else
	BLOCK_ERASE         = 0xD8,
#endif
	READ_JEDEC_ID		= 0x9F,
	DUMMY_BYTE		 	= 0xFF,
};

/**
 * @brief Init W25Q64 Flash
 * 
 * @return true 
 * @return false 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
bool W25Q64_Flash_Init(void);

/**
 * @brief Read W25Q64 Info
 * 
 * @return uint32_t 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */

uint32_t W25Q64_Read_Info(void);

/**
 * @brief Enable Write
 * 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void W25Q64_Write_Enable(void);

/**
 * @brief Disable Write
 * 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void W25Q64_Write_Disable(void);

#endif