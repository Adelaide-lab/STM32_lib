#ifndef __COMMON__
#define __COMMON__
#include "stm32f10x.h"

#define BSP_EVENT(prestr, str, timeout) \
    {                                   \
#str, prestr##_##str, timeout   \
    }
typedef struct
{
    char *evt_str;
    uint32_t evt;
    uint16_t evt_wait_timeout;
} bsp_evt_struct;

#define BSP_FAST_FLAG_TIMEOUT 0x100
#define BSP_LONG_FLAG_TIMEOUT 0x1000

#endif