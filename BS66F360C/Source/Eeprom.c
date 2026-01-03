
#include	"EEPROM.h"

unsigned char read_eeprom(unsigned char addr_data)
{
	unsigned char read_data;
	
    _eea=addr_data;
    _mp1l=0x40;
    _mp1h=0x01;
    
    _iar1|=0b00000010;//RDEN=1
    _iar1|=0b00000001;//RD=1
    
    while(_iar1&0b00000001);
    /*{
	 	GCC_CLRWDT();
    }*/
    _iar1&=0b11111101;//rden=0x00;
	_mp1h=0x00;
	read_data=_eed;
	return(read_data);
}

void writer_eeprom(unsigned char addr_data,unsigned char data)
{
	_eea=addr_data;
 	_eed=data;
 	
    _mp1l=0x40;
    _mp1h=0x01;
    
    _emi = 0;
    _iar1|=0b00001000; //_wren=1;
    _iar1|=0b00000100; //_wr=1;
    _emi = 1;
     
	while(_iar1&0b00000100);//while(_wr);
	/*{
		GCC_CLRWDT();
	}*/
    _iar1&=0b11111011;//_wr=0x00;
   _mp1h=0x00;
}


unsigned char	EEPROM_ReadBytes(unsigned char u8v_readAdd)
{
	unsigned char gu8v_data1,gu8v_data2,gu8v_check,gu8v_cal;
	gu8v_data1 = read_eeprom(u8v_readAdd);
	gu8v_data2 = read_eeprom(u8v_readAdd+1);
	gu8v_check = read_eeprom(u8v_readAdd+2);
	gu8v_cal = gu8v_data1+gu8v_data2;
	if(gu8v_check == gu8v_cal)
	{
		gu16v_EeTemp = gu8v_data2*256+gu8v_data1;
		return	1;
	}
	else
	{
		gu8v_data1 = read_eeprom(u8v_readAdd+3);
		gu8v_data2 = read_eeprom(u8v_readAdd+4);
		gu8v_check = read_eeprom(u8v_readAdd+5);
		
		gu8v_cal = gu8v_data1+gu8v_data2;
		 
		if(gu8v_check == gu8v_cal)
		{
			gu16v_EeTemp = gu8v_data2*256+gu8v_data1;
			return	1;
		}
		else
		{
			return	0;
		}
	}
}

unsigned char	EEPROM_WriteBytes(unsigned char u8v_WriteAdd,unsigned int u16v_intWritedata)
{	
	unsigned char gu8v_data1,gu8v_data2,gu8v_check,gu8v_cal;
	gu8v_data1 = (unsigned char)(u16v_intWritedata);
	gu8v_data2 = (unsigned char)(u16v_intWritedata>>8);
	gu8v_check = gu8v_data1+gu8v_data2; 
	writer_eeprom(u8v_WriteAdd,gu8v_data1);
	writer_eeprom(u8v_WriteAdd+1,gu8v_data2);
	writer_eeprom(u8v_WriteAdd+2,gu8v_check);
	gu8v_data1 = read_eeprom(u8v_WriteAdd);
	gu8v_data2 = read_eeprom(u8v_WriteAdd+1);
	gu8v_check = read_eeprom(u8v_WriteAdd+2);
	gu8v_cal = gu8v_data1+gu8v_data2;
	if(gu8v_check == gu8v_cal)
	{
		return	1;
	}
	else
	{
		return	0;
	}
}