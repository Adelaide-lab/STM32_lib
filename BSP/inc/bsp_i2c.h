#ifndef  __BSP_I2C__
#define __BSP_I2C__
#include "stm32f10x.h"

#define I2C_FAST_FLAG_TIMEOUT				0x1000

// IIC
#define  EEPROM_I2C                   							I2C1
#define  EEPROM_I2C_CLK               			RCC_APB1Periph_I2C1
#define  EEPROM_I2C_APBxClkCmd       RCC_APB1PeriphClockCmd
#define  EEPROM_I2_BAUDRATE           400000

//IIC GPIO Òý½Åºê¶¨Òå
#define  EEPROM_I2C_SCL_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  EEPROM_I2C_SDA_GPIO_CLK           (RCC_APB2Periph_GPIOB)

#define  EEPROM_I2C_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  EEPROM_I2C_SCL_GPIO_PORT         GPIOB  
#define  EEPROM_I2C_SCL_GPIO_PIN          GPIO_Pin_6

#define  EEPROM_I2C_SDA_GPIO_PORT       GPIOB
#define  EEPROM_I2C_SDA_GPIO_PIN        GPIO_Pin_7



void OLED_I2C_Init(void);
//void OLED_Init(void);
//uint8_t OLED_Write(uint8_t data, uint8_t mode);
//void OLED_Read(uint8_t data);
//void OLED_Clear_Screen(void);
//void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
//void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode);
//void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode);
//uint8_t OLED_Refresh(void);
//void OLED_Show(uint8_t *p_buff);
//void OLED_ColorTurn(u8 i);
//void OLED_DisplayTurn(u8 i);
//void OLED_DisPlay_On(void);
uint8_t u8x8_gpio_and_delay_hw(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


#endif