
#include "led.h"

void LED_initF(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);	 

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;				 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB,&GPIO_InitStructure);					
	GPIO_SetBits(GPIOB,GPIO_Pin_4);						
}

void LED_turnF(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_4))
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);		
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_4);
}
