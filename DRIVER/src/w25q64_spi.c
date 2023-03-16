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
	SPI_Wait_Event()
		fot(int i = 0; i < 3; i++)
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
