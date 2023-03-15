/**
 * @file bsp_i2c.h
 * @author Adelaide (1479398604xz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) github:Adelai-lab 2023
 *
 */
#ifndef __BSP_I2C__
#define __BSP_I2C__

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"

#define I2C I2C1
#define I2C_CLK RCC_APB1Periph_I2C1
#define I2C_APBxClkCmd RCC_APB1PeriphClockCmd
#define I2C_BAUDRATE 400000

#define I2C_SCL_GPIO_CLK (RCC_APB2Periph_GPIOB)
#define I2C_SDA_GPIO_CLK (RCC_APB2Periph_GPIOB)

#define I2C_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd

#define I2C_SCL_GPIO_PORT GPIOB
#define I2C_SCL_GPIO_PIN GPIO_Pin_6

#define I2C_SDA_GPIO_PORT GPIOB
#define I2C_SDA_GPIO_PIN GPIO_Pin_7

/**
 * @brief I2C Init Function
 *
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void I2C_Bsp_Init(void);

/**
 * @brief I2C Search Event
 *
 * @param evt
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t I2C_Search_Event(uint32_t evt);

/**
 * @brief I2C wait data
 *
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint16_t I2C_Wait_Data(uint32_t evt);

/**
 * @brief Generate Start Signal
 *
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t I2C_Start_Generator(void);

/**
 * @brief Generate Stop Signal
 *
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void I2C_Stop_Generator(void);

/**
 * @brief Select Master As Transmitter
 *
 * @param slave_address
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t I2C_Transmitter_Selected(uint8_t slave_address);

/**
 * @brief Select Master As Receiver
 *
 * @param slave_address
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t I2C_Receiver_Selected(uint8_t slave_address);

/**
 * @brief I2C send one byte data
 *
 * @param send_data
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t I2C_Send_DataByte(uint8_t send_data);

/**
 * @brief I2C receive one byte data
 *
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t I2C_Receive_DataByte(void);

/**
 * @brief I2C send data buffer
 *
 * @param s_buf
 * @param num_bytes
 * @return uint8_t
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t I2C_Send_DataBytes(uint8_t *s_buf, uint8_t num_bytes);

/**
 * @brief I2C receive data buffer
 *
 * @param r_buf
 * @param num_bytes
 * @return uint8_t*
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t *I2C_Receive_DataBytes(uint8_t *r_buf, uint8_t num_bytes);

#endif