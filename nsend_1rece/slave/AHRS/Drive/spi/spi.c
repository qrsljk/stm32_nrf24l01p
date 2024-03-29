
#include "spi.h"

void SPI1_initF(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1,ENABLE);
 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7); 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_6); 

	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex; 
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;		
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;		
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;		
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;	
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;		
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;		
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial=7;
	SPI_Init(SPI1,&SPI_InitStructure); 
 
	SPI_Cmd(SPI1,ENABLE);
	
	SPI1_readWriteByteF(0xFF);
	SPI1_setSpeedF(SPI_BaudRatePrescaler_4);
}   
void SPI1_setSpeedF(u8 baudRatePre)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(baudRatePre));
	SPI1->CR1&=0XFFC7;
	SPI1->CR1|=baudRatePre;
	SPI_Cmd(SPI1,ENABLE); 
} 
u8 SPI1_readWriteByteF(u8 txData)
{		
	u8 retry=0;				 	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET) 
	{
		retry++;
		if(retry>200)
			return 0;
	}			  
	SPI_I2S_SendData(SPI1,txData); 
	
	retry=0;
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET) 
	{
		retry++;
		if(retry>200)
			return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI1);  
}
