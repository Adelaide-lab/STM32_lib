/**
 * @file oled.c
 * @author Adelaide (1479398604xz@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) github:Adelai-lab 2023
 * 
 */
#include "oled.h"
#include "bsp_i2c.h"

/* Mode: 1 for command, 0 for data*/
uint8_t OLED_Write(uint8_t data, uint8_t mode)
{
	if(!I2C_Start_Generator())
	{
		return 0;
	}

	if(!I2C_Transmitter_Selected(OLED_Address))
	{
		return 0;
	}

	if(mode == 1)
	{
		if(!I2C_Send_DataByte(OLED_COMMAND))
		{
			return 0;
		}
	}
	else if (mode == 0)
	{
		if(!I2C_Send_DataByte(OLED_DATA))
		{
			return 0;
		}
	}	

	if(!I2C_Send_DataByte(data))
	{
		return 0;
	}

	I2C_Stop_Generator();
	return 1;
}

// void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t)
// {
// 	uint8_t i,m,n;
// 	i=y/8;
// 	m=y%8;
// 	n=1<<m;
// 	if(t){OLED_GRAM[x][i]|=n;}
// 	else
// 	{
// 		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
// 		OLED_GRAM[x][i]|=n;
// 		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
// 	}
// }

// uint8_t OLED_Refresh(void)
// {
// 	uint8_t i,n;
// 	for(i=0;i<4;i++)
// 	{
// 		OLED_Write(0xb0+i,Cmd_Mode);
// 		OLED_Write(0x00,Cmd_Mode);
// 		OLED_Write(0x10,Cmd_Mode);
// 		I2C_GenerateSTART(I2C1,ENABLE);
// 		while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) == RESET)
// 		{
// 			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
// 		}
// 		I2CTimeout = I2C_FAST_FLAG_TIMEOUT;
// 		I2C_Send7bitAddress(I2C1,OLED_Address,I2C_Direction_Transmitter);
// 		while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == RESET)
// 		{
// 				if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
// 		}
// 		I2C_SendData(I2C1,0x78);
// 		while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET)
// 		{
// 				if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
// 		}
// 		I2C_SendData(I2C1,0x40);
// 		while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET)
// 		{
// 				if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(4);
// 		}
// 		for(n=0;n<128;n++)
// 		{
// 			I2C_SendData(I2C1,OLED_GRAM[n][i]);
// 			while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET)
// 			{
// 					if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(5);
// 			}
// 		}
// 		I2C_GenerateSTOP(I2C1,ENABLE);
//   }
// 		return 0;
// }

// void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode)
// {
// 	uint8_t i,m,temp,size2,chr1;
// 	uint8_t x0=x,y0=y;
// 	if(size1==8)size2=6;
// 	else size2=(size1/8+((size1%8)?1:0))*(size1/2); 
// 	chr1=chr-' ';  
// 	for(i=0;i<size2;i++)
// 	{
// 		if(size1==8)
// 		{temp=asc2_0806[chr1][i];} 
// 		else if(size1==12)
//         {temp=asc2_1206[chr1][i];} 
// 		else if(size1==16)
//         {temp=asc2_1608[chr1][i];} 
// 		else return;
// 		for(m=0;m<8;m++)
// 		{
// 			if(temp&0x01)OLED_DrawPoint(x,y,mode);
// 			else OLED_DrawPoint(x,y,!mode);
// 			temp>>=1;
// 			y++;
// 		}
// 		x++;
// 		if((size1!=8)&&((x-x0)==size1/2))
// 		{x=x0;y0=y0+8;}
// 		y=y0;
//   }
// }

// void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode)
// {
// 	while((*chr>=' ')&&(*chr<='~'))
// 	{
// 		OLED_ShowChar(x,y,*chr,size1,mode);
// 		if(size1==8)x+=6;
// 		else x+=size1/2;
// 		chr++;
//   }
// }

// void OLED_Clear_Screen(void)
// {
// 		uint8_t i,n;
// 		for(i=0;i<8;i++)
// 		{
// 				OLED_Write (0xb0+i,Cmd_Mode);
// 				OLED_Write (0x00,Cmd_Mode);
// 				OLED_Write (0x10,Cmd_Mode);
// 				for(n=0;n<128;n++)
// 				OLED_Write (0x00,Data_Mode);
// 		}
// }

void OLED_Init(void)
{

	sysdelay_mil_secs(500);

	OLED_Write(0xAE,Cmd_Mode); /*display off*/

	OLED_Write(0x00,Cmd_Mode); /*set lower column address*/
	OLED_Write(0x10,Cmd_Mode); /*set higher column address*/

	OLED_Write(0x40,Cmd_Mode); /*set display start line*/

	OLED_Write(0xB0,Cmd_Mode); /*set page address*/

	OLED_Write(0x81,Cmd_Mode); /*contract control*/
	OLED_Write(0xFF,Cmd_Mode); /*128*/

	OLED_Write(0xA1,Cmd_Mode); /*set segment remap*/

	OLED_Write(0xA6,Cmd_Mode); /*normal / reverse*/

	OLED_Write(0xA8,Cmd_Mode); /*multiplex ratio*/
	OLED_Write(0x1F,Cmd_Mode); /*duty = 1/32*/

	OLED_Write(0xC8,Cmd_Mode); /*Com scan direction*/

	OLED_Write(0xD3,Cmd_Mode); /*set display offset*/
	OLED_Write(0x00,Cmd_Mode);

	OLED_Write(0xD5,Cmd_Mode); /*set osc division*/
	OLED_Write(0x80,Cmd_Mode);

	OLED_Write(0xD9,Cmd_Mode); /*set pre-charge period*/
	OLED_Write(0x1f,Cmd_Mode);

	OLED_Write(0xDA,Cmd_Mode); /*set COM pins*/
	OLED_Write(0x01,Cmd_Mode);

	OLED_Write(0xdb,Cmd_Mode); /*set vcomh*/
	OLED_Write(0x30,Cmd_Mode);

	OLED_Write(0x8d,Cmd_Mode); /*set charge pump enable*/
	OLED_Write(0x14,Cmd_Mode);

	OLED_Write(0xAF,Cmd_Mode);

	sysdelay_mil_secs(200);
}

// void OLED_ColorTurn(uint8_t i)
// {
// 	if(i==0)
// 	{
// 		OLED_Write(0xA6,OLED_COMMAND);
// 	}
// 	if(i==1)
// 	{
// 		OLED_Write(0xA7,OLED_COMMAND);
// 	}
// }

// void OLED_DisplayTurn(uint8_t i)
// {
// 	if(i==0)
// 	{
// 		OLED_Write(0xC8,Cmd_Mode);
// 		OLED_Write(0xA1,Cmd_Mode);
// 	}
// 	if(i==1)
// 	{
// 		OLED_Write(0xC0,Cmd_Mode);
// 		OLED_Write(0xA0,Cmd_Mode);
// 	}
// }

// void OLED_DisPlay_On(void)
// {
// 	OLED_Write(0x8D,Cmd_Mode);
// 	OLED_Write(0x14,Cmd_Mode);
// 	OLED_Write(0xAF,Cmd_Mode);
// }

uint8_t u8x8_gpio_and_delay_hw(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
            break;
    case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
            break;
    case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
            sysdelay_mil_secs(1);
            break;
    case U8X8_MSG_DELAY_I2C:      // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
            break;                // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
            break;                // arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
            break;                // arg_int=1: Input dir with pullup high for I2C data pin
    case U8X8_MSG_GPIO_MENU_SELECT:
            break;
    case U8X8_MSG_GPIO_MENU_NEXT:
            break;
    case U8X8_MSG_GPIO_MENU_PREV:
            break;
    case U8X8_MSG_GPIO_MENU_HOME:
            break;
    default:
            return 0;
            break;
    }
    return 1;
}

uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    uint8_t *data = (uint8_t *)arg_ptr;
    switch (msg)
    {
    case U8X8_MSG_BYTE_SEND:
		I2C_Send_DataBytes(data,arg_int);
		break;
    case U8X8_MSG_BYTE_INIT:
		/* add your custom code to init i2c subsystem */
		OLED_I2C_Init();
		break;
    case U8X8_MSG_BYTE_SET_DC:
		/* ignored for i2c */
		break;
    case U8X8_MSG_BYTE_START_TRANSFER:
		I2C_Start_Generator();
		I2C_Transmitter_Selected(OLED_Address);
		break;
    case U8X8_MSG_BYTE_END_TRANSFER:
		I2C_Stop_Generator();
            break;
    default:
		return 0;
    }
}
