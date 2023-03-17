#include "bsp_uart.h"

void usart_init(void)
{
	GPIO_InitTypeDef GPIO_USART1_TX;
	GPIO_InitTypeDef GPIO_USART1_RX;
	USART_InitTypeDef USART1_InitStruct;
	NVIC_InitTypeDef NVIC_USART1_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_USART1_TX.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_USART1_TX.GPIO_Pin=GPIO_Pin_9;
	GPIO_USART1_TX.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_USART1_RX.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_USART1_RX.GPIO_Pin=GPIO_Pin_10;
	GPIO_USART1_RX.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_USART1_TX);
	GPIO_Init(GPIOA,&GPIO_USART1_RX);
	
	USART1_InitStruct.USART_BaudRate = 115200;
	USART1_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART1_InitStruct.USART_Parity = USART_Parity_No;
	USART1_InitStruct.USART_StopBits = USART_StopBits_1;
	USART1_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART1_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&USART1_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_USART1_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_USART1_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_USART1_InitStruct.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_USART1_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_USART1_InitStruct);
}

void usart_Sendbyte(USART_TypeDef* USARTx, uint8_t Data)
{
	USART_SendData(USARTx,Data);
	 while(USART_GetFlagStatus(USARTx,USART_IT_TXE)==RESET);
}

void usart_SendString(USART_TypeDef* USARTx, uint8_t *String)
{
		uint8_t ByteData;
		while(*String!='\0')
		{
			ByteData=*String++;
			usart_Sendbyte(USARTx,ByteData);
				}
		while(USART_GetFlagStatus(USARTx,USART_IT_TC)==RESET);
}

int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (uint8_t) ch);
		
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

void USART1_IRQHandler(void)
{
	 uint8_t temp;
	 if (USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)
	 {
			temp = USART_ReceiveData(USART1);
		  if(temp == '\n' || temp == '\r' || temp == '\t')
			{ 
				 printf("%c",temp);
			}
		  USART_SendData(USART1, temp);
	 }
}


