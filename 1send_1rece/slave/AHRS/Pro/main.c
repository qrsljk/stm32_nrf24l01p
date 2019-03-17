
#include "main.h"
     
extern u8 rfRxChG;
extern u8 rfTxChG;

extern u8 rfIrqRxFlagG;
extern u8 rfIrqTxFlagG;

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

int main(void) 
{
	DELAY_initF();      
	NVIC_confF();
	UART1_initF(115200);
	LED_initF();
	
	rfRxChG=5;
	
	SPI1_initF();
	RF_initF(rfRxChG); 
	EXTI2_initF();
	
	rfTxBufCh0[0]=8;
	rfTxBufCh1[0]=8;
	rfTxBufCh2[0]=8;
	rfTxBufCh3[0]=8;
	rfTxBufCh4[0]=8;
	rfTxBufCh5[0]=8;
	
  while(1)
  {
		
		if(rfIrqTxFlagG)
		{
			printf("%d	%d	%d	%d	%d	%d\n",	\
					rfRxBufCh0[0],rfRxBufCh1[0],rfRxBufCh2[0],rfRxBufCh3[0],rfRxBufCh4[0],rfRxBufCh5[0]);
			
			rfRxBufCh0[0]=0;
			rfRxBufCh1[0]=0;
			rfRxBufCh2[0]=0;
			rfRxBufCh3[0]=0;
			rfRxBufCh4[0]=0;
			rfRxBufCh5[0]=0;

			RF_writeRegF(RF_W_REGISTER+RF_STATUS,0xFF);  
			RF_writeRegF(RF_FLUSH_TX,0xFF); 
			RF_writeRegF(RF_FLUSH_RX,0xFF);
			
			rfIrqTxFlagG=0;
		}
				
	}
}
