
#include	"Aip1628.h"

//void	GCC_DELAY(unsigned char r_delay)
//{
//	while(r_delay--);
//}
/**************************************************************/ 
//
/**************************************************************/ 
void SendByte(unsigned char r_data) 
{ 
	unsigned char i; 
	for(i=0;i<8;i++) 
	{ 
		if(r_data & 0x01) 	P_DIO = 1; 
		else 								P_DIO = 0; 
		P_CLK = 0; 
		GCC_DELAY(10);
		P_CLK = 1; 
		GCC_DELAY(10);
		r_data >>= 1; 
	} 
	P_CLK = 0; 
	GCC_DELAY(10);
} 

/**************************************************************/ 
//
/**************************************************************/ 
void SendCommand(unsigned char r_command) 
{ 
	 P_STB = 1;
	 GCC_DELAY(5);
	 P_STB = 0; 
	 GCC_DELAY(5);
	 SendByte(r_command); 
} 

void	InitIoPort()
{
	P_STB = 1;	
	P_CLK = 0;
	P_DIO = 0;
}

//void Dis_SetledDriver(volatile unsigned char  *pBuffer,unsigned char  length)
//{
//	InitIoPort();
//	SendCommand(C_ComDisMod7Mul10);    
//	SendCommand(C_ComWRInc);    
//	SendCommand(C_ComAddress0);    	
//	while(length)
//	{
//		SendByte(*pBuffer);
//		SendByte(*pBuffer);
//		pBuffer++;
//		length--;
//	}
//	SendCommand(C_ComDisplayOn);   
//	P_STB = 1;
//}