#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__
#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include <stdio.h>

#define SPI SPI1
#define FLASH_SPI_APBxClock_FUN RCC_APB2PeriphClockCmd
#define FLASH_SPI_CLK RCC_APB2Periph_SPI1
#define FLASH_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define FLASH_SPI_GPIO_CLK (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC)

#define FLASH_SPI_CLK_PORT GPIOA
#define FLASH_SPI_CLK_PIN GPIO_Pin_5

#define FLASH_SPI_MISO_PORT GPIOA
#define FLASH_SPI_MISO_PIN GPIO_Pin_6

#define FLASH_SPI_MOSI_PORT GPIOA
#define FLASH_SPI_MOSI_PIN GPIO_Pin_7

/*chip select pin*/
#define FLASH_SPI_CS_PORT GPIOC
#define FLASH_SPI_CS_PIN GPIO_Pin_0

#define FLASH_SPI_CS_HIGH GPIO_SetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN)
#define FLASH_SPI_CS_LOW GPIO_ResetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN)

/**
 * @brief SPI Init Function
 *
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void SPI_Bsp_Init(void);

/**
 * @brief Config SPI Initialization Value
 *
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-04-29
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void SPI_Bsp_Config(void);

/**
 * @brief Search SPI Event
 *
 * @param evt
 * @return uint8_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint8_t SPI_Search_Event(uint32_t evt);

/**
 * @brief SPI wait event
 *
 * @param evt
 * @return uint16_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-17
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint16_t SPI_Wait_Event(uint32_t evt);

/**
 * @brief Start SPI Transmission/Recieve
 *
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void SPI_TransRecieve_Start(void);

/**
 * @brief Stop SPI Transmission/Recieve
 *
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void SPI_TransRecieve_Stop(void);

/**
 * @brief SPI send one byte data
 *
 * @param send_data
 * @return uint8_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint8_t SPI_Send_DataByte(uint8_t send_data);

/**
 * @brief SPI receive one byte data
 *
 * @return uint8_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint16_t SPI_Receive_DataByte(void);

/**
 * @brief SPI send data buffer
 *
 * @param s_buf
 * @param num_bytes
 * @return uint8_t
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint8_t SPI_Send_DataBytes(uint8_t *s_buf, uint8_t num_bytes);

/**
 * @brief SPI receive data buffer
 *
 * @param r_buf
 * @param num_bytes
 * @return uint8_t*
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint8_t *SPI_Receive_DataBytes(uint8_t *r_buf, uint8_t num_bytes);

#endif
