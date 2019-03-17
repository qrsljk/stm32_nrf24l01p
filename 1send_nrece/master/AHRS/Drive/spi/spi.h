
#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"

extern void SPI1_initF(void);		
extern void SPI1_setSpeedF(u8 baudRatePre);
extern u8   SPI1_readWriteByteF(u8 txData);
		     
#endif
