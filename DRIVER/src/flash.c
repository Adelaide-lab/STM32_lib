#include "flash.h"

	uint32_t flash_id = 0;
	
	FLASH_SPI_CS_LOW;
	SPI_SEND_DATA_Byte(READ_JEDEC_ID);
	
	flash_id = SPI_SEND_DATA_Byte(DUMMY_BYTE);
	flash_id <<= 8;
	
	flash_id |= SPI_SEND_DATA_Byte(DUMMY_BYTE); 
	flash_id <<= 8;
	
	flash_id |= SPI_SEND_DATA_Byte(DUMMY_BYTE); 
	FLASH_SPI_CS_HIGH;	
	
	return flash_id;