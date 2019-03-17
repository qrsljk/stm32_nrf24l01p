
#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"
#include "stdio.h"	
	
#define UARTX_printf USART1

extern void UART1_initF(u32 baudRate);
extern void UART_sendCharF(USART_TypeDef* USARTx,u8 txData);
extern void UART_txStatusF(USART_TypeDef* USARTx,int *txBuf);
extern void UART_txSenserF(USART_TypeDef* USARTx,int *txBuf);

#endif
