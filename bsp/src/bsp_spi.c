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
SPI_Bsp_Init(void)
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

void SPI_Bsp_Config(void)
{
	SPI_InitTypeDef SPI_InitStructure;

	SPI_Bsp_Init();
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
}

void SPI_TransRecieve_Start(void)
{
	GPIO_ResetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN);
}

void SPI_TransRecieve_STop(void)
{
	GPIO_SetBits(FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN);
}

uint8_t SPI_Send_DataByte(uint8_t send_data)
{
	SPI_TransRecieve_Start();
	uint16_t wait_timeout = 0x0;
	wait_timeout = SPI_Search_Event(SPI_I2S_FLAG_TXE);
	if (!wait_timeout)
	{
		return 0;
		SPI_TransRecieve_Stop();
	}

	SPI_I2S_SendData(SPI, data);
	wait_timeout = SPI_Search_Event(SPI_I2S_FLAG_RXNE);
	if (!wait_timeout)
	{
		return 0;
		SPI_TransRecieve_Stop();
	}
	SPI_TransRecieve_Stop();
}

uint16_t SPI_Receive_DataByte(void)
{
	SPI_I2S_ReceiveData(SPI);
}

uint8_t SPI_Send_DataBytes(uint8_t *s_buf, uint8_t num_bytes)
{
	if ((num_bytes--) && (SPI_Send_DataByte(*s_buf)))
	{
		s_buf++;
	}
}

uint8_t *SPI_Receive_DataBytesSPI_Receive_DataByte(uint8_t *r_buf, uint8_t num_bytes)
{
	while (num_bytes)
	{
		*r_buf = I2C_Receive_DataByte();
		r_buf++;
		num_bytes--;
	}
}

uint8_t SPI_Search_Event(uint32_t evt)
{
	uint16_t wait_timeout;
	uint8_t evt_num;

	evt_num = SPI_Wait_Event(evt);
	if (evt_num == 0xff)
	{
		return 0;
	}

	wait_timeout = I2C_Event_Info[evt_num].evt_wait_timeout;

	while (SPI_I2S_GetFlagStatus(I2C, I2C_Event_Info[evt_num].evt) == RESET)
	{
		if (wait_timeout-- == 0)
		{
			printf("wait evt:%s,timeout\r\n", I2C_Event_Info[evt_num].evt_str);
			return 0;
		}
	}
	return wait_timeout;
}

uint16_t SPI_Wait_Event(uint32_t evt)
{
	uint8_t evt_size = sizeof(SPI_Event_Info) / sizeof(bsp_evt_struct);
	uint8_t evt_num = 0;
	for (; evt_num < evt_size; evt_num++)
	{
		if (evt == SPI_Event_Info[evt_num].evt)
		{
			return evt_num;
		}
	}
	printf("I2C evt not valid\r\n");
	return 0xff;
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
