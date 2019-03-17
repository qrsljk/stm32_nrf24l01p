
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
	 
	rfTxChG=5;
	
	SPI1_initF();
	RF_initF(rfTxChG);
	TIM2_intInitF(999,71);  //1ms
	EXTI2_initF();

	rfTxBufCh0[0]=1;
	rfTxBufCh1[0]=2;
	rfTxBufCh2[0]=3;
	rfTxBufCh3[0]=4;
	rfTxBufCh4[0]=5;
	rfTxBufCh5[0]=6;
	
  while(1)
  {
		
		if(rfIrqRxFlagG)
		{
			printf("%d	%d	%d	%d	%d	%d\n",	\
					rfRxBufCh0[0],rfRxBufCh1[0],rfRxBufCh2[0],rfRxBufCh3[0],rfRxBufCh4[0],rfRxBufCh5[0]);
		
			rfRxBufCh0[0]=0;
			rfRxBufCh1[0]=0;
			rfRxBufCh2[0]=0;
			rfRxBufCh3[0]=0;
			rfRxBufCh4[0]=0;
			rfRxBufCh5[0]=0;
			
			rfIrqRxFlagG=0;
		}

	}
}
