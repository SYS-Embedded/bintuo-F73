
#ifndef 		_FUNCTION_H
#define 		_FUNCTION_H

#include	"MyDefine.h"
#include	"Variants.h"

void 	Function_Task(void);
extern	void 			Beep (unsigned char bp_type);
extern	unsigned char 	read_eeprom(unsigned char addr_data);
extern	void 			writer_eeprom(unsigned char addr_data,unsigned char data);
extern	unsigned char	EEPROM_WriteBytes(unsigned char u8v_WriteAdd,unsigned int u16v_intWritedata);
extern	unsigned char	EEPROM_ReadBytes(unsigned char u8v_readAdd);
extern	void 	Work_StatusRegInit(void);
extern	void  	Sys_Init(void);
extern	void 	Work_SensorAdcRegInit(void);
extern	void 	Init_TimerReg(void);
extern	void 	FactoryMode_Task(void);
#endif 		