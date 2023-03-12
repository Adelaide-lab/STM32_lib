#ifndef __BSP_SYSDELAY_H__
#define __BSP_SYSDELAY_H__
#include "stm32f10x.h"
#include "misc.h"
#include "core_cm3.h"

void sysdelay_init(void);

void sysdelay_micro_secs(uint32_t delay_times);

void sysdelay_mil_secs(uint32_t delay_times);

void sysdelay_secs(uint32_t delay_times);

	
#endif

