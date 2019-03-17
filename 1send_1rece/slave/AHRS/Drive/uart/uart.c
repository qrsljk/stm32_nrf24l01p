
#include "uart.h" 
		
int TxBuf[18];
		
#pragma import(__use_no_semihosting)             
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;  
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{      
	while((UARTX_printf->SR&0X40)==0) {}
  UARTX_printf->DR = (u8) ch;      
	return ch;
}

void UART1_initF(u32 baudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_DeInit(USART1); 
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 

	USART_InitStructure.USART_BaudRate=baudRate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	
	USART_Init(USART1,&USART_InitStructure); 
	
	USART_Cmd(USART1,ENABLE);
}
void UART_sendCharF(USART_TypeDef* USARTx,u8 txData)
{
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET); 
    USARTx->DR=txData;  
} 
void UART_txStatusF(USART_TypeDef* USARTx,int *txBuf)
{
	u8 byte_ctr,sum;
	u8 TxTemp[12];
	for(byte_ctr=0;byte_ctr<6;byte_ctr+=2) 
	{
		TxTemp[byte_ctr]=(txBuf[byte_ctr/2]&0xff00)>>8;
		TxTemp[byte_ctr+1]=txBuf[byte_ctr/2]&0x00ff;
	}
	TxTemp[6]=(txBuf[6]&0xff000000)>>24;
	TxTemp[7]=(txBuf[7]&0x00ff0000)>>16;
	TxTemp[8]=(txBuf[8]&0x0000ff00)>>8;
	TxTemp[9]=txBuf[9]&0x000000ff;
	TxTemp[10]=txBuf[10];
	TxTemp[11]=txBuf[11];
	UART_sendCharF(USARTx,0xAA); 
	UART_sendCharF(USARTx,0xAA); 
	UART_sendCharF(USARTx,0x01);
	UART_sendCharF(USARTx,12);	 
	for(byte_ctr=0;byte_ctr<12;byte_ctr++) 
	{
		UART_sendCharF(USARTx,TxTemp[byte_ctr]); 
		sum+=TxTemp[byte_ctr];
	}
	sum+=(0xAA+0xAA+0x01+12);
	UART_sendCharF(USARTx,sum); 
}
void UART_txSenserF(USART_TypeDef* USARTx,int *txBuf)
{
	u8 byte_ctr,sum;
	u8 TxTemp[18];
	for(byte_ctr=0;byte_ctr<18;byte_ctr+=2) 
	{
		TxTemp[byte_ctr]=(txBuf[byte_ctr/2]&0xff00)>>8;
		TxTemp[byte_ctr+1]=txBuf[byte_ctr/2]&0x00ff;
	}
	UART_sendCharF(USARTx,0xAA); 
	UART_sendCharF(USARTx,0xAA);
	UART_sendCharF(USARTx,0x02); 
	UART_sendCharF(USARTx,18);	
	for(byte_ctr=0;byte_ctr<18;byte_ctr++) 
	{
		UART_sendCharF(USARTx,TxTemp[byte_ctr]);
		sum+=TxTemp[byte_ctr];
	}
	sum+=(0xAA+0xAA+0x02+18);
	UART_sendCharF(USARTx,sum); 	
}
