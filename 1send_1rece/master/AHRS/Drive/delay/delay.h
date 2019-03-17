
#ifndef __DELAY_H
#define __DELAY_H  

#include "stm32f10x.h"

extern void DELAY_initF(void);
extern void DELAY_usF(u32 nus);
extern void DELAY_msF(u16 nms);

#endif
