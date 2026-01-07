
#ifndef 		_DISPLAY_H
#define 		_DISPLAY_H

#include	"MyDefine.h"
#include	"Variants.h"

void 	Display_Task (void);
extern	void	Fun_AllDcfOff(void);
extern	void	Fun_AllDcfOn(void);
extern	void	Fun_SetPumpFre(unsigned char mode);
//extern	void	AIP650_SendBytes(volatile unsigned char  *pBuffer,unsigned char length);
extern	void	AIP650_InitPort(void);
extern	void	AIP650_Start(void);
extern	void	AIP650_SendCMD(unsigned int cmd);		//È«ÁÁ
extern	void	AIP650_End(void);
extern	void	AIP650_SendByte(unsigned char Sdata);
extern	void SendCommand(unsigned char r_command); 	
extern	void SendByte(unsigned char r_data); 	
extern	void SendCommand(unsigned char r_command); 	
extern	void InitIoPort(void);

#endif 			