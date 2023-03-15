#include "bsp_spi.h"
#include "common.h"

static bsp_evt_struct SPI_Event_Info[8] =
    {
        BSP_EVENT(SPI_I2S, FLAG_RXNE,
                  BSP_FAST_FLAG_TIMEOUT),
        BSP_EVENT(SPI_I2S, FLAG_TXE,
                  BSP_FAST_FLAG_TIMEOUT),
        BSP_EVENT(SPI_I2S, FLAG_BSY,
                  BSP_FAST_FLAG_TIMEOUT),
        BSP_EVENT(SPI_I2S, FLAG_OVR,
                  BSP_FAST_FLAG_TIMEOUT),
        BSP_EVENT(SPI, FLAG_MODF,
                  BSP_FAST_FLAG_TIMEOUT),
        BSP_EVENT(SPI, FLAG_CRCERR,
                  BSP_FAST_FLAG_TIMEOUT),
        BSP_EVENT(I2S, FLAG_UDR,
                  BSP_FAST_FLAG_TIMEOUT),
        BSP_EVENT(I2S, FLAG_CHSIDE,
                  BSP_FAST_FLAG_TIMEOUT)}

void
SPI_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruture;
    FLASH_GPIO_APBxClock_FUN(FLASH_SPI_GPIO_CLK, ENABLE);
    FLASH_SPI_APBxClock_FUN(FLASH_SPI_CLK, ENABLE);

    GPIO_InitStruture.GPIO_Pin = FLASH_SPI_MISO_PIN;
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStruture);

    GPIO_InitStruture.GPIO_Pin = FLASH_SPI_MOSI_PIN;
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStruture);

    GPIO_InitStruture.GPIO_Pin = FLASH_SPI_CLK_PIN;
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_CLK_PORT, &GPIO_InitStruture);

    /*chip select*/
    GPIO_InitStruture.GPIO_Pin = FLASH_SPI_CS_PIN;
    GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStruture);
    /* set gpio for 3.3V*/
    FLASH_SPI_CS_HIGH;
}

void SPI_Config_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;

    SPI_GPIO_Init();
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

    SPI_Init(FLASH_SPIx, &SPI_InitStructure);
    SPI_Cmd(FLASH_SPIx, ENABLE);
}

uint8_t SPI_SEND_DATA_Byte(uint8_t data)
{
    SPITimeout = BSP_FAST_FLAG_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_TXE) == RESET)
    {
        if ((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(WAIT_TIMEOUT);
    }

    SPI_I2S_SendData(FLASH_SPIx, data);

    SPITimeout = BSP_FAST_FLAG_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(FLASH_SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if ((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(WAIT_TIMEOUT);
    }

    return SPI_I2S_ReceiveData(FLASH_SPIx);
}

uint8_t SPI_FLASH_Read_Byte(void)
{
    return SPI_SEND_DATA_Byte(DUMMY_BYTE);
}

uint32_t SPI_Read_ID(void)
{
}

void SPI_WIRTE_ENABLE(void)
{
    FLASH_SPI_CS_LOW;
    SPI_SEND_DATA_Byte(WRITE_ENABLE);
    FLASH_SPI_CS_HIGH;
}

void SPI_WRITE_DIASBLE(void)
{
    FLASH_SPI_CS_LOW;
    SPI_SEND_DATA_Byte(WRITE_DISABLE);
    FLASH_SPI_CS_HIGH;
}

void SPI_FLASH_WAIT_OPERATION(void)
{
    uint8_t flash_status = 0;

    FLASH_SPI_CS_LOW;
    do
    {
        flash_status = SPI_SEND_DATA_Byte(READ_STATUS_REG1);
    } while (flash_status & BUSY_BIT);

    FLASH_SPI_CS_HIGH;
}

void SPI_FLASH_ERASE_SECTOR(uint32_t addr)
{
    SPI_WIRTE_ENABLE();
    SPI_FLASH_WAIT_OPERATION();

    FLASH_SPI_CS_LOW;
    SPI_SEND_DATA_Byte(SECTOR_ERASE);
    SPI_SEND_DATA_Byte((addr >> 16) & (0xff));
    SPI_SEND_DATA_Byte((addr >> 8) & (0xff));
    SPI_SEND_DATA_Byte((addr) & (0xff));

    FLASH_SPI_CS_HIGH;
    SPI_FLASH_WAIT_OPERATION();
}

void SPI_FLASH_PAGE_WRITE(uint8_t *p_buff, uint32_t addr, uint32_t bytes_num)
{

    SPI_WIRTE_ENABLE();
    SPI_FLASH_WAIT_OPERATION();

    FLASH_SPI_CS_LOW;
    SPI_SEND_DATA_Byte(PAGE_PROGRAM);
    SPI_SEND_DATA_Byte((addr >> 16) & (0xff));
    SPI_SEND_DATA_Byte((addr >> 8) & (0xff));
    SPI_SEND_DATA_Byte((addr) & (0xff));

    if (bytes_num > MAX_PAGE_WRITE_SIZE)
    {
        SPI_TIMEOUT_UserCallback(PAGE_WRITE_ERROR);
    }

    while (bytes_num--)
    {
        SPI_SEND_DATA_Byte(*p_buff);
        p_buff++;
    }

    FLASH_SPI_CS_HIGH;
    SPI_FLASH_WAIT_OPERATION();
}
