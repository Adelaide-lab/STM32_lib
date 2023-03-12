/**
 * @file led.h
 * @author Adelaide (1479398604xz@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) github:Adelai-lab 2023
 * 
 */
#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"
#include "bsp_sysdelay.h"

#define LED_R 0
#define LED_G 1
#define LED_B 2

#define IS_COLOR_VALID(COLOR) ( COLOR == LED_R || \
                                COLOR == LED_G || \
                                COLOR == LED_B  )
/**
 * @brief turn off led
 * 
 * @param color 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void led_off(uint8_t color);

/**
 * @brief turn on led
 * 
 * @param color 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void led_on(uint8_t color);

/**
 * @brief toggle led 
 * 
 * @param color 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void led_toggle(uint8_t color);

/**
 * @brief led blink with systick
 * 
 * @param time 
 * @param color 
 * @version 0.1
 * @author Adelaide (1479398604xz@gmail.com)
 * @date 2023-03-12
 * @copyright Copyright (c) github:Adelai-lab 2023
 */
void led_blink(uint8_t time,uint32_t color);

#endif