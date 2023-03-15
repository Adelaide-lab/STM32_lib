#ifndef __COMMON__
#define __COMMON__

#define I2C_EVENT(str, timeout) \
    {                           \
#str,                   \
            I2C_EVENT_##str,    \
            timeout             \
    }
typedef struct
{
    char *evt_str;
    uint32_t evt;
    uint16_t evt_wait_timeout;
} i2c_evt_struct;

#define BSP_FAST_FLAG_TIMEOUT 0x100
#define BSP_LONG_FLAG_TIMEOUT 0x1000

#endif