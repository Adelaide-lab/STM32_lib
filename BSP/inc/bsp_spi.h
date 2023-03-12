#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__	
#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include <stdio.h>

#define SPI_EVENT(str,timeout) {#str,\
    SPI_##str,\
    timeout}

typedef struct{
    char *     evt_str;
    uint16_t   evt;
    uint16_t   evt_wait_timeout;
}spi_evt_struct;

#define SPI_FAST_FLAG_TIMEOUT 0x100
#define SPI_LONG_FLAG_TIMEOUT 0x1000

#define MAX_PAGE_WRITE_SIZE 256
#define  BUSY_BIT    0x1
#define  WEL_BIT     0x2
#define  BP_BITS		  0x1C
#define  TB_BIT					0x20
#define  SEC_BIT			0x40
#define  SRP0_BIT		0x80
#define  SPI_FAST_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define  SPI_LONG_FLAG_TIMEOUT         ((uint32_t)10*(0x1000))

#define  FLASH_SPIx                                             SPI1
#define  FLASH_SPI_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define  FLASH_SPI_CLK				                             RCC_APB2Periph_SPI1
#define  FLASH_GPIO_APBxClock_FUN					 RCC_APB2PeriphClockCmd
#define  FLASH_SPI_GPIO_CLK                        (RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC)

#define FLASH_SPI_CLK_PORT                         GPIOA
#define FLASH_SPI_CLK_PIN													   GPIO_Pin_5

#define FLASH_SPI_MISO_PORT                       GPIOA
#define FLASH_SPI_MISO_PIN													 GPIO_Pin_6

#define FLASH_SPI_MOSI_PORT                       GPIOA
#define FLASH_SPI_MOSI_PIN													 GPIO_Pin_7

/*chip select pin*/
#define FLASH_SPI_CS_PORT                         GPIOC
#define FLASH_SPI_CS_PIN													   GPIO_Pin_0

#define FLASH_SPI_CS_HIGH  		GPIO_SetBits(FLASH_SPI_CS_PORT,FLASH_SPI_CS_PIN)
#define FLASH_SPI_CS_LOW 		  GPIO_ResetBits(FLASH_SPI_CS_PORT,FLASH_SPI_CS_PIN)



void SPI_GPIO_Init(void);
void SPI_Cofig_Init(void);
uint8_t SPI_SEND_DATA_Byte(uint8_t);
uint8_t SPI_FLASH_Read_Byte(void);

void SPI_WIRTE_ENABLE(void);
void SPI_WRITE_DIASBLE(void);
void SPI_FLASH_WAIT_OPERATION(void);
void SPI_FLASH_ERASE_SECTOR(uint32_t addr);
void SPI_FLASH_PAGE_WRITE(uint8_t *p_buff, uint32_t addr, uint32_t bytes_num);
#endif
