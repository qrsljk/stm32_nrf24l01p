
#include "delay.h"

u8  facUsG;
u16 facMsG;

void DELAY_initF(void)	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	facUsG=SystemCoreClock/8000000;	
	facMsG=(u16)facUsG*1000;
}	
void DELAY_usF(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*facUsG;   		 
	SysTick->VAL=0x00;       
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          
	do {
		temp=SysTick->CTRL;
	} while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      
	SysTick->VAL =0X00;       
}
void DELAY_msF(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*facMsG;
	SysTick->VAL =0x00;           
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;        
	do {
		temp=SysTick->CTRL;
	} while(temp&0x01&&!(temp&(1<<16))); 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      
	SysTick->VAL =0X00;      	    
} 
