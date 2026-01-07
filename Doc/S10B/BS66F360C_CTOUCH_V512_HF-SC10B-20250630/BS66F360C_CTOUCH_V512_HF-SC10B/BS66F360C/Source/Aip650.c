

#include "Aip650.h"

void  	AIP650_InitPort(void)
{
	P_SCLK = 1;	
	P_DIN = 1;
}

void  	AIP650_Start(void)	
{
	P_SCLK = 1;	
	P_DIN = 1;
	P_DIN = 0;
	GCC_DELAY(10);
	P_SCLK = 0;	
}

void  	AIP650_End(void)	
{
	P_DIN = 0;
	GCC_DELAY(10);
	P_SCLK = 1;	
	GCC_DELAY(10);
	P_DIN = 1;
	GCC_DELAY(10);
}


void	AIP650_SendByte(unsigned char Sdata)
{
	unsigned char n;
	for(n=0;n<8;n++)
	{
		if(Sdata&0x80)	P_DIN = 1;
		else								P_DIN = 0;
		GCC_DELAY(5);
		P_SCLK = 1;	
		GCC_DELAY(5);
		P_SCLK = 0;	
		Sdata <<=1;
	}
  	GCC_DELAY(5);
	P_SCLK = 1;
	GCC_DELAY(5);
	P_SCLK = 0;	
}

void	AIP650_SendCMD(unsigned int cmd)
{
	AIP650_SendByte((unsigned char)(cmd>>8));
	AIP650_SendByte((unsigned char)(cmd));
}
//void	AIP650_CommandOFF(void)
//{
//	AIP650_InitPort();
//	AIP650_Start();
//	AIP650_SendCMD(C_CommandDisplayOff);		//Command3
//	AIP650_End();
//}

//void	AIP650_SendBytes(volatile unsigned char  *pBuffer,unsigned char length)
//{
//	AIP650_InitPort();
//	AIP650_Start();
//	AIP650_SendCMD(C_CommandDisplayOn);		//È«ÁÁ
//	AIP650_End();
//	while(length)	
//	{
//		AIP650_Start();
//		switch(length)
//		{
//			case 4:
//				AIP650_SendByte(C_CommandDIG0);
//			break;
//			case 3:
//				AIP650_SendByte(C_CommandDIG1);
//			break;
//			case 2:
//				AIP650_SendByte(C_CommandDIG2);
//			break;
//			case 1:
//				AIP650_SendByte(C_CommandDIG3);
//			break;
//		}
//		AIP650_SendByte(*pBuffer);
//		pBuffer++;
//		length--;
//	}
//	AIP650_End();
//}

