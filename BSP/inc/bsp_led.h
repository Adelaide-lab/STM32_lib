#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"
#include "bsp_sysdelay.h"
#include "bsp_key.h"


void led_init(void);
void led_off(uint32_t color);
void led_on(uint32_t color);
void led_toggle(uint32_t color);
void led_blink(uint32_t time,uint32_t color);

#endif 
