/**
 * @file w25q64_spi.h
 * @author Adelaide (1479398604xz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) github:Adelai-lab 2023
 *
 */
#ifndef __W25Q64_H__
#define __Q25Q64_H__
#include "stm32f10x.h"

enum w25q64_cmd
{
    DUMMY_WORD,
    WRITE_STATUS_REG = 0x01,
    PAGE_PROGRAM = 0x02,
    WRITE_DISABLE = 0x04,
    READ_STATUS_REG1 = 0x05,
    WRITE_ENABLE = 0x06,
    SECTOR_ERASE = 0x20,
    READ_STATUS_REG2 = 0x35,
    READ_UNIC_ID = 0x4B,
#if defined(USE_OF_32K)
    BLOCK_ERASE = 0x52,
#else
    BLOCK_ERASE = 0xD8,
#endif
    CHIP_ERASED1 = 0x60,
    ERASE_SUSPEND = 0x75,
    ERASE_RESUME = 0x7A,
    MANU_FACTURE_ID = 0x90,
    READ_JEDEC_ID = 0x9F,
    HIGH_PERF_MODE = 0xA3,
    RELEASE_POW_DN = 0xAB,
    PWR_DOWN = 0xB9,
    CHIP_ERASED2 = 0xC7,
    READ_MODE_RESET = 0xFF
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
 * @param info
 * @return true
 * @return false
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
bool W25Q64_Read_Info(uint32_t *info);

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

/**
 * @brief Wait operation
 *
 * @return uint32_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint32_t W25Q64_Wait_Operation(void);

/**
 * @brief Erase Sector
 *
 * @param addr
 * @return uint32_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint32_t W25Q64_Erase_Sector(uint32_t addr);

/**
 * @brief Write Page
 *
 * @param addr
 * @param p_buff
 * @param bytes_num
 * @return uint32_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint32_t W25Q64_Page_Write(uint32_t addr, uint8_t *p_buff, uint32_t bytes_num);

/**
 * @brief Erase the whole chip
 *
 * @return true
 * @return false
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
bool W25Q64_Chip_Erase(void);

/**
 * @brief Suspend Erase Execution
 *
 * @return true
 * @return false
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
bool W25Q64_Erase_Suspend(void);

/**
 * @brief Resume Erase Execution
 *
 * @return true
 * @return false
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
bool W25Q64_Erase_Resume(void);

/**
 * @brief Power Down To Low Power Mode
 *
 * @return true
 * @return false
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
bool W25Q64_Power_Down(void);

/**
 * @brief Resume Power Down
 *
 * @return true
 * @return false
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
bool W25Q64_Release_Power_Down(void);

#endif