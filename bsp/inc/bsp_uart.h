#ifndef __BSP_UART_H__
#define __BSP_UART_H__	
#include "stm32f10x.h"
#include "stdio.h"
#define MAX_SIZE_LENGTH 50


void usart_init(void);
void usart_Sendbyte(USART_TypeDef* USARTx, uint8_t Data);
void usart_SendHalfword(USART_TypeDef* USARTx, uint16_t Data);
void usart_SendWord(USART_TypeDef* USARTx, uint32_t Data);
void usart_SendString(USART_TypeDef* USARTx, uint8_t *String);
void usart_SendArrary(USART_TypeDef* USARTx, uint32_t *String);
void usart_ReciveString(USART_TypeDef* USARTx);

#endif
