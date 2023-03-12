#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__
#include "stm32f10x.h"

#define KEY_ON  1
#define KEY_OFF 0

void key_init(void);
uint8_t key_scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
