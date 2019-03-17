
#include "exti.h"

void EXTI2_initF(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);	 
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_2); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);

	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 

	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;					
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;							
	NVIC_Init(&NVIC_InitStructure);  
}


u8 rfRxChG;
u8 rfTxChG;

u8 rfIrqRxFlagG;
u8 rfIrqTxFlagG;

u8 rfRxBufCh0[32];  u8 rfRxBufLenCh0=32;
u8 rfRxBufCh1[32];  u8 rfRxBufLenCh1=32;
u8 rfRxBufCh2[32];  u8 rfRxBufLenCh2=32;
u8 rfRxBufCh3[32];  u8 rfRxBufLenCh3=32;
u8 rfRxBufCh4[32];  u8 rfRxBufLenCh4=32;
u8 rfRxBufCh5[32];  u8 rfRxBufLenCh5=32;

u8 rfTxBufCh0[32];  u8 rfTxBufLenCh0=32;
u8 rfTxBufCh1[32];  u8 rfTxBufLenCh1=32;
u8 rfTxBufCh2[32];  u8 rfTxBufLenCh2=32;
u8 rfTxBufCh3[32];  u8 rfTxBufLenCh3=32;
u8 rfTxBufCh4[32];  u8 rfTxBufLenCh4=32;
u8 rfTxBufCh5[32];  u8 rfTxBufLenCh5=32;

void EXTI2_IRQHandler(void)
{	
	u8 sta;
	
	if( (rfIrqTxFlagG) && (!RF_getIrq()) )
	{
		sta=RF_irqRxAckF(rfTxChG);
		rfIrqTxFlagG=0;
		
		if( (!rfIrqRxFlagG) && (sta==RF_RX_OK) )
			rfIrqRxFlagG=1;
	}

	LED_turnF();
	
	EXTI_ClearITPendingBit(EXTI_Line2); 
}
