#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"
#include "bsp_sysdelay.h"
#include "bsp_key.h"


#define LED_R  0
#define LED_G  1
#define LED_B  2

#define IS_COLOR_VALID(COLOR)  (COLOR==LED_R|| \
															  COLOR==LED_G|| \
																COLOR==LED_B)

void led_init(void);
void led_off(uint32_t color);
void led_on(uint32_t color);
void led_toggle(uint32_t color);
void led_blink(uint32_t time,uint32_t color);

#endif 
