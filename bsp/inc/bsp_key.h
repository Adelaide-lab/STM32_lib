/**
 * @file bsp_key.h
 * @author Adelaide (1479398604xz@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) github:Adelai-lab 2023
 * 
 */
#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__
#include "stm32f10x.h"

#define KEY_ON  1
#define KEY_OFF 0

/**
 * @brief 
 * 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void key_gpio_init(void);

/**
 * @brief 
 * 
 * @param GPIOx 
 * @param GPIO_Pin 
 * @return uint8_t 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
uint8_t key_scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
