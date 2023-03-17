#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_sysdelay.h"
#include "bsp_uart.h"
#include "bsp_spi.h"
#include "bsp_i2c.h"
#include "u8x8.h"
#include "u8g2.h"
#include "apds_9960.h"
#include "SG90.h"

u8g2_t u8g2;
extern int gesture_motion_;

int main(void)
{
		uint32_t id;
	  uint8_t capacity;
	  uint8_t mem_type;
	  uint8_t manu_id;
	  uint8_t capacity_in_mega;
		uint32_t time = 1000;
		
		led_init();
		key_init();
		sysdelay_init();
		usart_init();
		SPI_Config_Init();
		OLED_I2C_Init();
	  SparkFun_APDS9960_init();
	  id = SPI_Read_ID();
	  capacity    =  (id&0xff);
	  mem_type =  ((id>>8)&0xff);
	  manu_id    =  ((id>>16)&0xff);
	  capacity_in_mega = (1<<capacity)/(1024*1024);
	  printf("%x\n",id);
	  printf("manufacture id:%02x, memory type:%02x, capcity:%02x  %dMB\r\n",manu_id,mem_type,capacity,capacity_in_mega);
		Servor_Init();
		while(1)
		{

		}
}

