
#include	"Display.h"
#include    "drv_tm1652.h"

#define		C_LED_NUM3_ADD				0
#define		C_LED_NUM2_ADD				1
#define		C_LED_NUM1_ADD				2
#define		C_LED_KEY_ADD1				3
#define		C_LED_KEY_ADD2				4
#define		C_LED_KEY_ADD3				5

#define 	C_SEG_A	 					0x01
#define 	C_SEG_B	 					0x02
#define 	C_SEG_C	 					0x04
#define 	C_SEG_D	 					0x08
#define 	C_SEG_E	 					0x10
#define 	C_SEG_F	 					0x20
#define 	C_SEG_G	 					0x40
#define 	C_SEG_DP	 				0x80

#define 	C_NUM0	 					(C_SEG_A|C_SEG_B|C_SEG_C|C_SEG_D|C_SEG_E|C_SEG_F)
#define 	C_NUM1	 					(C_SEG_B|C_SEG_C)
#define 	C_NUM2	 					(C_SEG_A|C_SEG_B|C_SEG_D|C_SEG_E|C_SEG_G)
#define 	C_NUM3	 					(C_SEG_A|C_SEG_B|C_SEG_C|C_SEG_D|C_SEG_G)
#define 	C_NUM4	 					(C_SEG_B|C_SEG_C|C_SEG_F|C_SEG_G)
#define 	C_NUM5	 					(C_SEG_A|C_SEG_C|C_SEG_D|C_SEG_F|C_SEG_G)
#define 	C_NUM6	 					(C_SEG_A|C_SEG_C|C_SEG_D|C_SEG_E|C_SEG_F|C_SEG_G)
#define 	C_NUM7	 					(C_SEG_A|C_SEG_B|C_SEG_C)
#define 	C_NUM8	 					(C_SEG_A|C_SEG_B|C_SEG_C|C_SEG_D|C_SEG_E|C_SEG_F|C_SEG_G)
#define 	C_NUM9	 					(C_SEG_A|C_SEG_B|C_SEG_C|C_SEG_D|C_SEG_F|C_SEG_G)

#define 	C_CHAR_C	 				(C_SEG_A|C_SEG_D|C_SEG_E|C_SEG_F)
#define 	C_CHAR_A	 				(C_SEG_A|C_SEG_B|C_SEG_C|C_SEG_E|C_SEG_F|C_SEG_G)
#define 	C_CHAR_K	 				(C_SEG_E|C_SEG_F|C_SEG_G)
#define 	C_CHAR_E	 				(C_SEG_A|C_SEG_D|C_SEG_E|C_SEG_F|C_SEG_G)
#define 	C_CHAR_r	 				(C_SEG_E|C_SEG_G)
#define 	C_CHAR_O	 				(C_SEG_C|C_SEG_D|C_SEG_E|C_SEG_G)

const unsigned char  R_NumTable[10]={C_NUM0,C_NUM1,C_NUM2,C_NUM3,C_NUM4,C_NUM5,C_NUM6,C_NUM7,C_NUM8,C_NUM9};

void Dis_SetDisBufferAll(unsigned char gubv_setData)
{
	unsigned char n;
	for(n=0;n<8;n++)
	{
		gu8v_DisplayBuf[n]=gubv_setData;
	}
}


void Display_Refresh_To_TM1652(void)
{
    //number
    drv_tm1652_setdigit(0, gu8v_DisplayBuf[C_LED_NUM1_ADD]); // Grid 1
    drv_tm1652_setdigit(1, gu8v_DisplayBuf[C_LED_NUM1_ADD]); // Grid 2


    //led 
    drv_tm1652_setdigit(2, gu8v_DisplayBuf[2]); // Grid 3
    drv_tm1652_setdigit(3, gu8v_DisplayBuf[3]); // Grid 4
    drv_tm1652_setdigit(4, gu8v_DisplayBuf[4]); // Grid 5
}


void Display_Task (void)
{	
	//unsigned char u8_DisTemp,u8_DisTemp1,u8_DisTemp2;
	volatile unsigned char  *pBuffer;
	unsigned char disNum,r_Num3,r_Num2,r_Num1,length;
	
	Dis_SetDisBufferAll(0x00);
	switch(gu8v_WorkMode)
	{
		case C_POWER_ON_MODE:
			Dis_SetDisBufferAll(0xFF);
		break;
		case C_WORK_OFF_MODE:
			gu8v_DisplayBuf[C_LED_KEY_ADD3] |= C_SEG_E|C_SEG_F;//led22 led23
		break;
		case  C_WORK_ON_MODE :
				if(gubv_FactoryTestMode)
				{
					if(gubv_CalMode)
					{
						gu8v_DisplayBuf[C_LED_KEY_ADD3] |= C_SEG_B;//���水��
						switch(gu8v_CalModeIndex)
						{
							case 0:
								gu8v_DisplayBuf[C_LED_NUM3_ADD] =  C_CHAR_C;
								gu8v_DisplayBuf[C_LED_NUM2_ADD] =  C_CHAR_A;
								gu8v_DisplayBuf[C_LED_NUM1_ADD] =  R_NumTable[0];
								if(!gubv_GetZeroData)
								{
									gu8v_CalModeIndex = 1;
								}
							break;
							case 1:
								gu8v_DisplayBuf[C_LED_NUM3_ADD] =  C_CHAR_C;
								gu8v_DisplayBuf[C_LED_NUM2_ADD] =  C_CHAR_A;
								gu8v_DisplayBuf[C_LED_NUM1_ADD] =  R_NumTable[1];
							break;
							case 2:
								gu8v_DisplayBuf[C_LED_NUM3_ADD] =  C_CHAR_C;
								gu8v_DisplayBuf[C_LED_NUM2_ADD] =  C_CHAR_A;
								gu8v_DisplayBuf[C_LED_NUM1_ADD] =  R_NumTable[2];
							break;
							case 3:
								gu8v_DisplayBuf[C_LED_NUM2_ADD] =  C_CHAR_O;
								gu8v_DisplayBuf[C_LED_NUM1_ADD] =  C_CHAR_K;
							break;
							default:
								if(gubv_500mS_Flash) 
								{
									gu8v_DisplayBuf[C_LED_NUM3_ADD] =  C_CHAR_E;
									gu8v_DisplayBuf[C_LED_NUM2_ADD] =  C_CHAR_r;
									gu8v_DisplayBuf[C_LED_NUM1_ADD] =  C_CHAR_r;
								}
							break;
						}
					}
					else
					{
						if(gubv_500mS_Flash) 
						{
							Dis_SetDisBufferAll(0xFF);
						}
					}
				}
				else
				{
					if(gu8v_PreKeyDownDisTime)
					{
						if(!gubv_500mS_Flash)
						{
						    if(gu8v_PressureMode > 4)
                                gu8v_PressureMode = 4;
							disNum = gu8v_PressureMode+1;
							//r_Num2 =  disNum/10;
							r_Num1 =  disNum%10;
							gu8v_DisplayBuf[C_LED_NUM3_ADD] =  R_NumTable[r_Num1];
							gu8v_DisplayBuf[C_LED_NUM2_ADD] =  R_NumTable[r_Num1];
							gu8v_DisplayBuf[C_LED_NUM1_ADD] =  R_NumTable[r_Num1];
						}
					}
					else
					{
						if((!gubv_FunPressureFirstFull)&&(WorkModeFlag.byte))
						{
							gu8v_DisplayBuf[C_LED_NUM2_ADD] =  R_NumTable[4]|C_SEG_DP;	
							gu8v_DisplayBuf[C_LED_NUM1_ADD] =  R_NumTable[0];
						}
						else
						{
							r_Num3 = gu8v_AbNumDisCurrentValue;
							r_Num1 =   r_Num3%100;	
							r_Num3 = r_Num3/100;
							r_Num2 =  r_Num1/10;
							r_Num1 =  r_Num1%10;
							if(r_Num3)	gu8v_DisplayBuf[C_LED_NUM3_ADD] =  R_NumTable[r_Num3];
							gu8v_DisplayBuf[C_LED_NUM2_ADD] =  R_NumTable[r_Num2]|C_SEG_DP;	
							gu8v_DisplayBuf[C_LED_NUM1_ADD] =  R_NumTable[r_Num1];
						}	
					}
					if(gubv_AutoMode)				gu8v_DisplayBuf[C_LED_KEY_ADD1] |= C_SEG_F;
					if(gubv_QiBeiMode)				gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_B;
					if(gubv_DcfLeftFanShenMode)		gu8v_DisplayBuf[C_LED_KEY_ADD1] |= C_SEG_DP;
					if(gubv_DcfRightFanShenMode)	gu8v_DisplayBuf[C_LED_KEY_ADD1] |= C_SEG_G;
					if(gubv_TaituiMode)				gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_A;
					
					if(gubv_LockStatus)				gu8v_DisplayBuf[C_LED_KEY_ADD3] |= C_SEG_A;
					if(gubv_VoliceOn)				gu8v_DisplayBuf[C_LED_KEY_ADD1] |= C_SEG_D;
					
					if(!gubv_AbPressureFull)		gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_G;
					
					gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_F;//normal led
					if(gubv_AbSensorErrAlarmMode||gubv_FunSensorErrAlarmMode)	gu8v_DisplayBuf[C_LED_KEY_ADD3] |= C_SEG_DP;//alerm blue led ,alarm red led
					else														gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_DP;//alerm blue led ,alarm red led
					gu8v_DisplayBuf[C_LED_KEY_ADD3] |= C_SEG_B|C_SEG_C;//led19 led20
					gu8v_DisplayBuf[C_LED_KEY_ADD3] |= C_SEG_E|C_SEG_F;//led22 led23	
					if(gubv_StaticMode)				gu8v_DisplayBuf[C_LED_KEY_ADD1] |= C_SEG_B;
					///if((!WorkModeFlag.byte)&&(!gubv_StaticMode))
					else
					{
						gu8v_DisplayBuf[C_LED_KEY_ADD1] |= C_SEG_A;
						switch(gu8v_JiaoTiMode)
						{
							case 2:
								gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_E;
							break;
							case 1:
								gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_D;
							break;
							default:
								gu8v_DisplayBuf[C_LED_KEY_ADD2] |= C_SEG_C;
							break;
						}
					}
				}
		break;
	}
	//Dis_SetledDriver(gu8v_DisplayBuf,7);
	length = 7;
	pBuffer = gu8v_DisplayBuf;

    #ifdef DEV_S10B
	InitIoPort();
	SendCommand(C_ComDisMod7Mul10);    
	SendCommand(C_ComWRInc);    	
	SendCommand(C_ComAddress0);    	
	while(length)
	{
		SendByte(*pBuffer);
		SendByte(0x00);
		pBuffer++;
		length--;
	}
	SendCommand(C_ComDisplayOn);
    #else
    Display_Refresh_To_TM1652();
    #endif
    
}
