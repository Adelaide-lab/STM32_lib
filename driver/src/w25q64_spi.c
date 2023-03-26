/**
 * @file w25q64_spi.c
 * @author Adelaide (1479398604xz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-17
 *
 * @copyright Copyright (c) github:Adelai-lab 2023
 *
 */
#include "w25q64_spi.h"
#include "bsp_spi.h"

bool W25Q64_Flash_Init(void)
{
    uint32_t chip_info;
    if (W25Q64_Read_Info(chip_info))
    {
        printf("")
    }
}

bool W25Q64_Read_Info(uint32_t *info)
{
    SPI_TransRecieve_Start();
    bool Read_info = false;
    *info = 0;
    SPI_Send_DataByte(READ_JEDEC_ID);
    SPI_Wait_Event() for (int i = 0; i < 3; i++)
    {
        *info = (SPI_Receive_DataByte()) << (8 * i) + *info;
    }

    if (*info ==)
    {
        Read_info = true;
    }
    SPI_TransRecieve_Stop();
    return Read_info;
}

void W25Q64_Write_Enable(void)
{
    SPI_TransRecieve_Start();
    SPI_Send_DataByte(WRITE_ENABLE);
    SPI_TransRecieve_Stop();
}

void W25Q64_Write_Disable(void)
{
    SPI_TransRecieve_Start();
    SPI_Send_DataByte(WRITE_DISABLE);
    SPI_TransRecieve_Stop();
}

bool W25Q64_Wait_Operation(void)
{
    SPI_Send_DataByte(READ_STATUS_REG1);
    do
    {

        /* code */
    } while (/* condition */);
}

uint32_t W25Q64_Erase_Sector(uint32_t addr)
{
    W25Q64_Write_Enable();
    SPI_Send_DataByte(SECTOR_ERASE);
    for (int i = 2; i >= 0; i++)
    {
        SPI_Send_DataByte(addr >> (2 * 8));
    }
    W25Q64_Write_Disable();
    W25Q64_Wait_Operation();
}

uint32_t W25Q64_Page_Write(uint32_t addr, uint8_t *p_buff, uint32_t bytes_num)
{
    W25Q64_Write_Enable();
    SPI_TransRecieve_Start();
    SPI_Send_DataByte(PAGE_PROGRAM);
    for (int i = 2; i >= 0; i++)
    {
        SPI_Send_DataByte(addr >> (2 * 8));
    }

    while (bytes_num--)
    {
        SPI_Send_DataByte(*p_buff++);
    }

    SPI_TransRecieve_Stop();
    W25Q64_Write_Disable();
}

bool W25Q64_Chip_Erase(void)
{
    W25Q64_Write_Enable();
    SPI_Send_DataByte(CHIP_ERASED2);
    W25Q64_Write_Disable();
    W25Q64_Wait_Operation();
}

bool W25Q64_Erase_Suspend(void)
{
}

bool W25Q64_Erase_Resume(void)
{
}