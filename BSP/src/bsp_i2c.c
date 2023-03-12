#include "bsp_i2c.h"
#include "bsp_sysdelay.h"
#include "oledfont.h"
#include <stdio.h>

static i2c_evt_struct I2C_Event_Info[16] =
{
    I2C_EVENT(SLAVE_TRANSMITTER_ADDRESS_MATCHED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_RECEIVER_ADDRESS_MATCHED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_RECEIVER_SECONDADDRESS_MATCHED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_GENERALCALLADDRESS_MATCHED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_BYTE_RECEIVED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_BYTE_TRANSMITTED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_ACK_FAILURE,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(SLAVE_STOP_DETECTED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(MASTER_MODE_SELECT,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(MASTER_TRANSMITTER_MODE_SELECTED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(MASTER_RECEIVER_MODE_SELECTED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(MASTER_BYTE_RECEIVED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(MASTER_BYTE_TRANSMITTING,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(MASTER_BYTE_TRANSMITTED,\ 
        I2C_LONG_FLAG_TIMEOUT),
    I2C_EVENT(MASTER_MODE_ADDRESS10,\ 
        I2C_LONG_FLAG_TIMEOUT),
}

void I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure; 


	I2C_GPIO_APBxClkCmd(I2C_SCL_GPIO_CLK|I2C_SDA_GPIO_CLK, ENABLE);
	I2C_APBxClkCmd(I2C_CLK, ENABLE);


	GPIO_InitStructure.GPIO_Pin = I2C_SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_GPIO_PIN;
	GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
	

	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = I2C_BAUDRATE; 
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2 ;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C ;
	I2C_InitStructure.I2C_OwnAddress1 = 0; 
	
	I2C_Init(I2C,&I2C_InitStructure);
	
	I2C_Cmd (I2C, ENABLE);	    
}

uint8_t I2C_Search_Event(uint32_t evt)
{
    uint8_t evt_size = sizeof(I2C_Event_Info)/sizeof(i2c_evt_struct);
    uint8_t evt_num  = 0;
    for (; evt_num < evt_size; evt_num++)
    {
        if (evt == I2C_Event_Info[evt_num].evt)
        {
            return evt_num;
        }
    }
    printf("I2C evt not valid\r\n");
    return 0xff;
}

uint16_t I2C_Wait_Event(uint32_t evt)
{
    uint16_t wait_timeout;
    uint8_t  evt_num;

    evt_num = I2C_Search_Event(evt);
    if(evt_num == 0xff)
    {
        return 0;
    }

    wait_timeout = I2C_Event_Info[evt_num].evt_wait_timeout;

    while (I2C_CheckEvent(I2C, I2C_Event_Info[evt_num].evt) == RESET)
    {
        if (wait_timeout-- == 0)
        {
            printf("wait evt:%s,timeout\r\n", I2C_Event_Info[evt_num].evt_str); 
            return 0;
        }
    }
    return wait_timeout;
}

uint16_t I2C_Start_Generator(void)
{
    I2C_GenerateSTART(I2C, ENABLE);
    return I2C_Wait_Event(I2C_EVENT_MASTER_MODE_SELECT);
}

void I2C_Stop_Generator(void)
{
    I2C_GenerateSTOP(I2C, ENABLE);
}

uint16_t I2C_Transmitter_Selected(uint8_t slave_address)
{
    I2C_Send7bitAddress(I2C1, slave_address, I2C_Direction_Transmitter);
    return I2C_Wait_Event(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)
} 

uint16_t I2C_Receiver_Selected(uint8_t slave_address)
{
    I2C_Send7bitAddress(I2C1, slave_address, I2C_Direction_Receiver);
    return I2C_Wait_Event(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
}

uint8_t I2C_Send_DataByte(uint8_t send_data);
{
    I2C_SendData(I2C1,data);
    uint16_t wait_timeout = I2C_Wait_Event(I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    if(wait_timeout != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t I2C_Receive_DataByte(void)
{
    uint16_t wait_timeout = I2C_Wait_Event(I2C_EVENT_MASTER_BYTE_RECEIVED);

    if (wait_timeout != 0)
    {
        return I2C_ReceiveData(I2C1)
    }
    else
    {
        return ff;
    }
}

uint8_t I2C_Send_DataBytes(uint8_t *s_buf, uint8_t num_bytes)
{
    while ((num_byte--) && (I2C_Send_DataByte(*s_buf)))
    {
        s_buf++;
    }
}

uint8_t *I2C_Receive_DataBytes(uint8_t *r_buf, uint8_t num_bytes)
{
    while (num_bytes)
    {
        if(num_bytes == 1)
        {
            I2C_AcknowledgeConfig(I2C, DISABLE);
        }

        *r_buf = I2C_Receive_DataByte();
        r_buf++; num_bytes--;
    }
}
