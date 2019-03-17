
#include "tim.h"

void TIM2_intInitF(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=arr; 
	TIM_TimeBaseStructure.TIM_Prescaler=psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 

	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure); 

	TIM_Cmd(TIM2,ENABLE); 		
}


u8 timeG;

extern u8 rfRxChG;
extern u8 rfTxChG;

extern u8 rfIrqRxFlagG;
extern u8 rfIrqTxFlagG;

void TIM2_IRQHandler(void)   
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET) 
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
				
		timeG++;
		if(timeG>=5)
		{
			timeG=0;
			if(!rfIrqTxFlagG)
			{
				RF_writeRegF(RF_W_REGISTER+RF_STATUS,0xFF);  
				RF_writeRegF(RF_FLUSH_TX,0xFF); 
				RF_writeRegF(RF_FLUSH_RX,0xFF);

				RF_irqTxF(rfTxChG);
				rfIrqTxFlagG=1;
			}
		}
			
	}
}
