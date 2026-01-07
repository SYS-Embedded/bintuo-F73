
#ifndef 		_INITIAL_H
#define 		_INITIAL_H


#include	"MyDefine.h"
#include	"Variants.h"

void 	Sys_Init(void);
void 	RAM_Init(void);
void 	User_Init(void);


extern  void 	Beep (unsigned char  bp_type);
extern	void 	Beep_Init(void);
extern	void 	Uart0_Init(void);
extern	void  Dis_RgbLedOFF(void);

#endif 		