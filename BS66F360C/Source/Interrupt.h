
#ifndef 		_INTERRUPT_H
#define 		_INTERRUPT_H

#include	"MyDefine.h"
#include	"Variants.h"

DEFINE_ISR(MF2_ISR, 0x20);

#include	"MyDefine.h"
#include	"Variants.h"
extern	unsigned char 	read_eeprom(unsigned char addr_data);

#endif 		