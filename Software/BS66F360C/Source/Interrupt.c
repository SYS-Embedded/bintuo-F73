
#include "Interrupt.h"

//===============================================================
//timer0
//Interval 125uS
//	
//	
//===============================================================
void MF2_ISR(void)	
{
	if(_ptmaf)
	{
		_ptmaf = 0;
        P_TEST =~P_TEST;
		gubv_ZeroStatus = P_ZERO;
		if(gubv_ZeroStatus!=gubv_ZeroStatusCopy)
		{
			gu8v_AcOffDebounce = 20;
			gu8v_AbPwmOutPinDuty = gu8v_AbPwmDuty;
			gu8v_AbPwmOutPinDelay = gu8v_AbPwmDelay;
			
			gu8v_FunPwmOutPinDuty = gu8v_FunPwmDuty;
			gu8v_FunPwmOutPinDelay = gu8v_FunPwmDelay;	
		}
		gubv_ZeroStatusCopy = gubv_ZeroStatus;
		if(gu8v_WorkMode==C_WORK_ON_MODE)
		{			
			if((gubv_DcfA||gubv_DcfB)&&(!gubv_AbMotoOff))
			{
				if(gu8v_AbPwmOutPinDelay)
				{
					gu8v_AbPwmOutPinDelay--;
				}
				else
				{
					if(gu8v_AbPwmOutPinDuty) gu8v_AbPwmOutPinDuty--;
					if(gu8v_AbPwmOutPinDuty)P_AB_MOTO = C_MOTO_ON;
					else					P_AB_MOTO = C_MOTO_OFF;
				}
			}
			else
			{
				P_AB_MOTO = C_MOTO_OFF;
			}
			if(WorkModeFlag.byte)
			{
				if((gubv_DcfQiBei||gubv_DcfRightFanShen||gubv_DcfLeftFanShen||gubv_DcfTaiTui)&&(!gubv_FunMotoOff))
				{
					if(gu8v_FunPwmOutPinDelay)
					{
						gu8v_FunPwmOutPinDelay--;
					}
					else
					{
						if(gu8v_FunPwmOutPinDuty) 	gu8v_FunPwmOutPinDuty--;
						if(gu8v_FunPwmOutPinDuty)	P_FUN_MOTO = C_MOTO_ON;
						else						P_FUN_MOTO = C_MOTO_OFF;
					}	
				}
				else
				{
					P_FUN_MOTO = C_MOTO_OFF;
				}
			}
			else
			{
				P_FUN_MOTO = C_MOTO_OFF;
			}
		}
		else
		{
			P_AB_MOTO = C_MOTO_OFF;
			P_FUN_MOTO = C_MOTO_OFF;
			//if((!gubv_FunPressureFull)&&(WorkModeFlag.byte))
		}
		//if((gu8v_WorkMode==C_WORK_ON_MODE)&&(!gubv_FunPressureFull)&&(WorkModeFlag.byte))
		/*if((gu8v_WorkMode==C_WORK_ON_MODE)&&(WorkModeFlag.byte))
		{
			if(gubv_DcfQiBei||gubv_DcfRightFanShen||gubv_DcfLeftFanShen||gubv_DcfTaiTui)
			{
				if(gu8v_FunPwmOutPinDelay)
				{
					gu8v_FunPwmOutPinDelay--;
				}
				else
				{
					if(gu8v_FunPwmOutPinDuty) 	gu8v_FunPwmOutPinDuty--;
					if(gu8v_FunPwmOutPinDuty)	P_FUN_MOTO = C_MOTO_ON;
					else						P_FUN_MOTO = C_MOTO_OFF;
				}	
			}
			else
			{
				P_FUN_MOTO = C_MOTO_OFF;
			}
		}
		else
		{
			P_FUN_MOTO = C_MOTO_OFF;
		}*/
		switch(gu8v_RfSendStep)
		{
			case C_RF_SEND_START:
				P_Voice = C_DATA_LOW;	
				if(gu8v_RfBitCycle) gu8v_RfBitCycle--;
				if(!gu8v_RfBitCycle)
				{
					gu8v_RfSendStep = C_RF_SEND_DATA;
					gu8v_RfSendByteCnt = 0x00;
					gu8v_RfSendBitCnt =  0x00;
				}
			break;
			case C_RF_SEND_DATA:
				if(!gu8v_RfBitCycle)
				{
					if(((gu8v_VoicePluse>>gu8v_RfSendBitCnt)&C_SEND_FIRST_BIT)==C_SEND_FIRST_BIT)	
					{
						gu8v_RfBitCycle = C_BIT_CYCLE;    //8
						gu8v_RfBitDuty = C_BIT_LONG_DUTY; //2
					}
					else
					{
						gu8v_RfBitCycle = C_BIT_CYCLE;
						gu8v_RfBitDuty = C_BIT_SHORT_DUTY;//6
					}
				}
				if(gu8v_RfBitCycle)	gu8v_RfBitCycle--;
				if(gu8v_RfBitCycle>=gu8v_RfBitDuty)
				{
					P_Voice = C_DATA_HIGH;
				}
				else
				{
					P_Voice = C_DATA_LOW;
					if(!gu8v_RfBitCycle)
					{
						gu8v_RfSendBitCnt++;
						if(gu8v_RfSendBitCnt>=8)	
						{
							gu8v_RfSendBitCnt = 0;
						
							gu8v_RfSendStep = C_RF_SEND_NULL;
						}
					}
				}
			break;
			default:
				gu8v_RfBitCycle = C_SEND_START_CYCLE;
				gu8v_RfSendByteCnt = 0;
				gu8v_RfSendBitCnt = 0;
				P_Voice = C_DATA_HIGH;
			break;
		}
		gubv_Pin433Read = P_IR;
		if(gu8v_Rf433ReadCopy != gubv_Pin433Read)
		{
			if(gubv_Pin433Read)
			{
				switch(gu8v_IrSampStep)
				{
					case 0:
						if(gu8v_433_L_Cnt>=C_RF433_BIT_TIME3_MIN && gu8v_433_L_Cnt<=C_RF433_BIT_TIME3_MAX)  
						{
							gu8v_433BitCnt = 0;
							gu8v_433ByteCnt = 0;
							gu8v_IrSampStep = 1;
						}
					break;
					case 1:
						gu8v_433BitCnt = 0;
						gu8v_433ByteCnt = 0;
						gu8v_IrSampStep = 2;
					break;
					case 2:
						if(((gu8v_433_H_cnt>=C_RF433_BIT_TIME2_MIN)&&(gu8v_433_H_cnt<=C_RF433_BIT_TIME2_MAX))&&((gu8v_433_L_Cnt>=C_RF433_BIT_TIME1_MIN)&&(gu8v_433_L_Cnt<=C_RF433_BIT_TIME1_MAX))) 
						{
							gu8v_433RecData[gu8v_433ByteCnt] |=(0x80>>gu8v_433BitCnt);
							gu8v_433BitCnt++;
						}
						else if(((gu8v_433_H_cnt>=C_RF433_BIT_TIME1_MIN)&&(gu8v_433_H_cnt<=C_RF433_BIT_TIME1_MAX))&&((gu8v_433_L_Cnt>=C_RF433_BIT_TIME2_MIN)&&(gu8v_433_L_Cnt<=C_RF433_BIT_TIME2_MAX)))
						{
							gu8v_433RecData[gu8v_433ByteCnt] &=~(0x80>>gu8v_433BitCnt);
							gu8v_433BitCnt++;
						}
						else
						{
							gu8v_433BitCnt = 0;
							gu8v_433ByteCnt = 0;
							gu8v_IrSampStep = 0;
						}
						if(gu8v_433BitCnt>=8)
						{
							gu8v_433BitCnt = 0;
							gu8v_433ByteCnt++;
							if(gu8v_433ByteCnt>=3)
							{
								gu8v_433ByteCnt = 0;
								gu8v_433RecValue[0] = gu8v_433RecData[0];
								gu8v_433RecValue[1] = gu8v_433RecData[1];
								gu8v_433RecValue[2] = gu8v_433RecData[2];
								gu8v_433RecData[0] = 0;
								gu8v_433RecData[1] = 0;
								gu8v_433RecData[2] = 0;
								gubv_IrRecUpdata = 1;
								gu8v_433BitCnt = 0;
								gu8v_433ByteCnt = 0;
								gu8v_IrSampStep = 0;
							}
						}
					break;
				}
				gu8v_433_H_cnt = 0;
				gu8v_433_L_Cnt = 0;
			}
		}
		else
		{
			if(gubv_Pin433Read)
			{
				if(gu8v_433_H_cnt<250)gu8v_433_H_cnt++;
			}
			else
			{
				if(gu8v_433_L_Cnt<250)gu8v_433_L_Cnt++;
			}
		}
		gu8v_Rf433ReadCopy = gubv_Pin433Read;
		gu8v_Delay5mS++;
		if(gu8v_Delay5mS>=40)
		{
			gu8v_Delay5mS = 0;
			gubv_5mS = 1;
			gu8v_Delay10mS++;
			if(gu8v_Delay10mS>=2)
			{
				gu8v_Delay10mS = 0;
				gubv_10mS = 1;
				
				if(gu8v_BeepTime)	gu8v_BeepTime--;
				gu8v_Delay50mS++;
				if(gu8v_Delay50mS>=5)
				{
					gu8v_Delay50mS = 0;
					gubv_50mS	= 1;
					gu8v_Delay100mS++;
					if(gu8v_Delay100mS>=2)
					{
						gu8v_Delay100mS = 0;
						gubv_100mS	= 1;
					}	
				}	
			}
		}
	}
}

void	Time_Base(void)
{
	if(gu8v_AbFangQiTime)
	{
		gu8v_AbFangQiTime--;
	}
	if(gu8v_PowerOnDelay)	
	{
		gu8v_PowerOnDelay--;
	}
	if(gu8v_RfIdCopyTime)		
	{
		gu8v_RfIdCopyTime--;
		if(!gu8v_RfIdCopyKeyCnt)		gu8v_RfIdCopyKeyCnt = 0;
	}
	if(gu8v_KeyLongDelay)				gu8v_KeyLongDelay--;
	if(gu8v_IrDelay)					gu8v_IrDelay--;
	if(gu8v_PreKeyDownDisTime)			gu8v_PreKeyDownDisTime--;
	if(gu8v_UartDelayClearRxIndex)
	{
		gu8v_UartDelayClearRxIndex--;
		if(!gu8v_UartDelayClearRxIndex)
		{
			gu8v_UartRxLength = 0;
		}
	}
	gu8v_Delay500mS++;
	if(gu8v_Delay500mS>=5)
	{
		gu8v_Delay500mS = 0;
		gubv_500mS = 1;
		gubv_500mS_1 = 1;
		gubv_500mS_Flash = ~gubv_500mS_Flash;
		gu8v_Delay1S++;
		if(gu8v_Delay1S>=2)
		{
			gu8v_Delay1S	= 0;
			gubv_1S = 1;
			gubv_1S_1 = 1;
			gubv_1S_2 = 1;
			gubv_1S_3 = 1;
			#if C_DEBUG_MODE
			#else
				if(gu8v_LockDelay60S)	
				{
					gu8v_LockDelay60S--;
					if(!gu8v_LockDelay60S)
					{
						gubv_LockStatus = 1;
					}
				}
			#endif
		}
	}				
}


