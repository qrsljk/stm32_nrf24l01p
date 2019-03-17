
#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_on()  GPIO_ResetBits(GPIOB,GPIO_Pin_4) 
#define LED_off() GPIO_SetBits(GPIOB,GPIO_Pin_4) 	

extern void LED_initF(void);
extern void LED_turnF(void);
			    
#endif
