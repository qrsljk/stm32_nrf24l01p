
#include "nrf24l01p.h"

extern u8 rfRxBufCh0[32];  extern u8 rfRxBufLenCh0;
extern u8 rfRxBufCh1[32];  extern u8 rfRxBufLenCh1;
extern u8 rfRxBufCh2[32];  extern u8 rfRxBufLenCh2;
extern u8 rfRxBufCh3[32];  extern u8 rfRxBufLenCh3;
extern u8 rfRxBufCh4[32];  extern u8 rfRxBufLenCh4;
extern u8 rfRxBufCh5[32];  extern u8 rfRxBufLenCh5;

extern u8 rfTxBufCh0[32];  extern u8 rfTxBufLenCh0;
extern u8 rfTxBufCh1[32];  extern u8 rfTxBufLenCh1;
extern u8 rfTxBufCh2[32];  extern u8 rfTxBufLenCh2;
extern u8 rfTxBufCh3[32];  extern u8 rfTxBufLenCh3;
extern u8 rfTxBufCh4[32];  extern u8 rfTxBufLenCh4;
extern u8 rfTxBufCh5[32];  extern u8 rfTxBufLenCh5;

#define rfRxAddrWidM 5 
#define rfTxAddrWidM 5 

u8 rfRxAddrCh0[rfRxAddrWidM] = {0x00,0x44,0x33,0x22,0x11};  
u8 rfTxAddrCh0[rfTxAddrWidM] = {0x00,0x44,0x33,0x22,0x11};  
u8 rfRxAddrCh1[rfRxAddrWidM] = {0x01,0x44,0x33,0x22,0x11}; 
u8 rfTxAddrCh1[rfTxAddrWidM] = {0x01,0x44,0x33,0x22,0x11};  
u8 rfRxAddrCh2[rfRxAddrWidM] = {0x02,0x44,0x33,0x22,0x11};
u8 rfTxAddrCh2[rfTxAddrWidM] = {0x02,0x44,0x33,0x22,0x11};  
u8 rfRxAddrCh3[rfRxAddrWidM] = {0x03,0x44,0x33,0x22,0x11}; 
u8 rfTxAddrCh3[rfTxAddrWidM] = {0x03,0x44,0x33,0x22,0x11}; 
u8 rfRxAddrCh4[rfRxAddrWidM] = {0x04,0x44,0x33,0x22,0x11}; 
u8 rfTxAddrCh4[rfTxAddrWidM] = {0x04,0x44,0x33,0x22,0x11}; 
u8 rfRxAddrCh5[rfRxAddrWidM] = {0x05,0x44,0x33,0x22,0x11};
u8 rfTxAddrCh5[rfTxAddrWidM] = {0x05,0x44,0x33,0x22,0x11};  

u8 rfRxAddrPn[6]      = {RF_RX_ADDR_P0,RF_RX_ADDR_P1,RF_RX_ADDR_P2,RF_RX_ADDR_P3,RF_RX_ADDR_P4,RF_RX_ADDR_P5};
u8 rfEnPn[6]          = {0x01,0x03,0x05,0x09,0x11,0x21};
u8 rfWriteAckPayPn[6] = {RF_W_ACK_PAYLOAD_P0,RF_W_ACK_PAYLOAD_P1,RF_W_ACK_PAYLOAD_P2,RF_W_ACK_PAYLOAD_P3,RF_W_ACK_PAYLOAD_P4,RF_W_ACK_PAYLOAD_P5};

u8 RF_checkF(void)  
{
	u8 i;
	u8 buf[5] = {0xA5,0xA5,0xA5,0xA5,0xA5};
	RF_writeRegsF(RF_W_REGISTER+RF_TX_ADDR,buf,5);
	for(i=0;i<5;i++)
		buf[i]=0;
	RF_readRegsF(RF_TX_ADDR,buf,5); 
	for(i=0;i<5;i++)
		if(buf[i]!=0xA5)
			break;	 							   
	if(i!=5)
		return ERROR;
	return SUCCESS;	
}	
void RF_confF(u8 ch)
{
	u8 sta;		    							
	sta=RF_readRegF(RF_STATUS);  	
	RF_writeRegF(RF_W_REGISTER+RF_STATUS,sta);  
	RF_writeRegF(RF_FLUSH_TX,0xFF); 
	RF_writeRegF(RF_FLUSH_RX,0xFF); 
	
	RF_ceEn();	
	switch (ch)
	{
		case 0:
			RF_writeRegsF(RF_W_REGISTER+RF_TX_ADDR,rfTxAddrCh0,rfTxAddrWidM);  
			RF_writeRegsF(RF_W_REGISTER+rfRxAddrPn[0],rfRxAddrCh0,rfRxAddrWidM);  
			break;
		case 1:
			RF_writeRegsF(RF_W_REGISTER+RF_TX_ADDR,rfTxAddrCh1,rfTxAddrWidM);  
			RF_writeRegsF(RF_W_REGISTER+rfRxAddrPn[0],rfRxAddrCh1,rfRxAddrWidM);  
			break;
		case 2:
			RF_writeRegsF(RF_W_REGISTER+RF_TX_ADDR,rfTxAddrCh2,rfTxAddrWidM);  
			RF_writeRegsF(RF_W_REGISTER+rfRxAddrPn[0],rfRxAddrCh2,rfRxAddrWidM);  
			break;
		case 3:
			RF_writeRegsF(RF_W_REGISTER+RF_TX_ADDR,rfTxAddrCh3,rfTxAddrWidM);  
			RF_writeRegsF(RF_W_REGISTER+rfRxAddrPn[0],rfRxAddrCh3,rfRxAddrWidM);  
			break;
		case 4:
			RF_writeRegsF(RF_W_REGISTER+RF_TX_ADDR,rfTxAddrCh4,rfTxAddrWidM);  
			RF_writeRegsF(RF_W_REGISTER+rfRxAddrPn[0],rfRxAddrCh4,rfRxAddrWidM);  
			break;
		case 5:
			RF_writeRegsF(RF_W_REGISTER+RF_TX_ADDR,rfTxAddrCh5,rfTxAddrWidM);  
			RF_writeRegsF(RF_W_REGISTER+rfRxAddrPn[0],rfRxAddrCh5,rfRxAddrWidM);  
			break;
	}
	RF_writeRegF(RF_W_REGISTER+RF_EN_AA,rfEnPn[ch]);     
	RF_writeRegF(RF_W_REGISTER+RF_EN_RXADDR,rfEnPn[ch]);  
	RF_writeRegF(RF_W_REGISTER+RF_SETUP_RETR,0x11); //´ýÐÞ¸Ä
	RF_writeRegF(RF_W_REGISTER+RF_RF_CH,40);       //´ýÐÞ¸Ä
	RF_writeRegF(RF_W_REGISTER+RF_RF_SETUP,0x0E);  
	RF_writeRegF(RF_W_REGISTER+RF_DYNPD,rfEnPn[ch]);      
	RF_writeRegF(RF_W_REGISTER+RF_FEATURE,0x06);
	RF_writeRegF(RF_W_REGISTER+RF_CONFIG,0x4A);  
	RF_ceDis();
}
void RF_initF(u8 ch)  
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);  
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_2); 

	DELAY_msF(500);
	while(!RF_checkF())
	{
		LED_on();						
		DELAY_msF(1000);
		LED_off();						 
		DELAY_msF(1000);
	}
	RF_confF(ch);
}

u8 RF_readRegF(u8 readAddr)   
{
	u8 readData;	
	RF_csnEn();
	SPI1_readWriteByteF(readAddr);
	readData=SPI1_readWriteByteF(0xFF);
	RF_csnDis();
	return readData;      
}	
void RF_writeRegF(u8 writeAddr,u8 writeData)  
{
	RF_csnEn();
	SPI1_readWriteByteF(writeAddr);
	SPI1_readWriteByteF(writeData);
	RF_csnDis();          		
}
void RF_readRegsF(u8 readAddr,u8 *readData,u8 len)  
{
	u8 byte_ctr;	
	RF_csnEn();
	SPI1_readWriteByteF(readAddr);
	for(byte_ctr=0;byte_ctr<len;byte_ctr++)
		readData[byte_ctr]=SPI1_readWriteByteF(0xFF);
	RF_csnDis();  
}
void RF_writeRegsF(u8 writeAddr,u8 *writeData,u8 len) 
{
	u8 byte_ctr;	
	RF_csnEn();
	SPI1_readWriteByteF(writeAddr);
	for(byte_ctr=0;byte_ctr<len;byte_ctr++)
		SPI1_readWriteByteF(writeData[byte_ctr]); 
	RF_csnDis();  
}

void RF_irqTxF(u8 ch) 
{
	RF_ceEn();
	switch (ch)
	{
		case 0:
			RF_writeRegsF(RF_W_TX_PAYLOAD,rfTxBufCh0,rfTxBufLenCh0);  
			break;
		case 1:
			RF_writeRegsF(RF_W_TX_PAYLOAD,rfTxBufCh1,rfTxBufLenCh1); 
			break;
		case 2:
			RF_writeRegsF(RF_W_TX_PAYLOAD,rfTxBufCh2,rfTxBufLenCh2); 
			break;
		case 3:
			RF_writeRegsF(RF_W_TX_PAYLOAD,rfTxBufCh3,rfTxBufLenCh3);
			break;
		case 4:
			RF_writeRegsF(RF_W_TX_PAYLOAD,rfTxBufCh4,rfTxBufLenCh4);
			break;
		case 5:
			RF_writeRegsF(RF_W_TX_PAYLOAD,rfTxBufCh5,rfTxBufLenCh5);
			break;
	}
	RF_ceDis(); 
}
u8 RF_irqRxAckF(u8 ch)
{
	u8 sta;
	sta=RF_readRegF(RF_STATUS);
	RF_writeRegF(RF_W_REGISTER+RF_STATUS,sta);
	if(sta&RF_TX_OK)  
	{
		if(sta&RF_RX_OK) 
		{
			switch (ch)
			{
				case 0:
					rfRxBufLenCh0=RF_readRegF(RF_R_RX_PL_WID);
					RF_readRegsF(RF_R_RX_PAYLOAD,rfRxBufCh0,rfRxBufLenCh0); 
					break;
				case 1:
					rfRxBufLenCh1=RF_readRegF(RF_R_RX_PL_WID);
					RF_readRegsF(RF_R_RX_PAYLOAD,rfRxBufCh1,rfRxBufLenCh1); 
					break;
				case 2:
					rfRxBufLenCh2=RF_readRegF(RF_R_RX_PL_WID);
					RF_readRegsF(RF_R_RX_PAYLOAD,rfRxBufCh2,rfRxBufLenCh2); 
					break;
				case 3:
					rfRxBufLenCh3=RF_readRegF(RF_R_RX_PL_WID);
					RF_readRegsF(RF_R_RX_PAYLOAD,rfRxBufCh3,rfRxBufLenCh3); 
					break;
				case 4:
					rfRxBufLenCh4=RF_readRegF(RF_R_RX_PL_WID);
					RF_readRegsF(RF_R_RX_PAYLOAD,rfRxBufCh4,rfRxBufLenCh4); 
					break;
				case 5:
					rfRxBufLenCh5=RF_readRegF(RF_R_RX_PL_WID);
					RF_readRegsF(RF_R_RX_PAYLOAD,rfRxBufCh5,rfRxBufLenCh5); 
					break;
			}
			return RF_RX_OK; 	
		}
		return RF_TX_OK;
	}	
	if(sta&RF_MAX_TX) 
	{
		RF_writeRegF(RF_FLUSH_TX,0XFF); 
		return RF_MAX_TX;
	}
	return ERROR; 
}
