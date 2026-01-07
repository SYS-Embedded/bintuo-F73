
#include "Function.h"


void	Fun_GenVoicePluse(unsigned char volcePluse)
{
	if(gubv_VoliceOn||volcePluse==C_VOICE_OFF||volcePluse==C_VOICE_BP_DIDI)
	{	
		gu8v_VoicePluse = volcePluse;
		gu8v_RfSendStep = C_RF_SEND_START;
		gu8v_RfBitCycle = C_SEND_START_CYCLE;
		gu8v_RfSendByteCnt = 0;
		gu8v_RfSendBitCnt = 0;
	}
}
void	Fun_InitWorkOffMode(void)
{
	gu8v_WorkMode = C_WORK_OFF_MODE;
	gu8v_AbFangQiTime = 0;
	gubv_AbSensorFangQiEn = 0;
}
void	Fun_InitWorkOnMode(void)
{
	gu8v_WorkMode = C_WORK_ON_MODE;
	gu8v_JiaoTiMode = 0;
	gu16v_JiaoTiTime = C_10_M;
	gu16v_JiaoTiTimeCmp = C_5_M;
	gu16v_JiaoTiTimeCnt = 0;
	gu8v_AbFangQiTime = 0;
	gubv_AbSensorFangQiEn = 0;
}
void	Fun_CalModeProcess(void)
{
	Beep(C_BP_NORMAL);
	switch(gu8v_CalModeIndex)
	{
		case 0:
	
		break;
		case 1://60mmHg	
			if((gu16v_Ab150CalDataEe>(gu16v_AbAdcZeroData+400))&&(gu16v_Fun150CalDataEe>(gu16v_FunAdcZeroData+400)))//0.2V
			{
				gubv_WriteCalEe = 1;
				gu16v_Ab150CalDataEeCopy = gu16v_Ab150CalDataEe;
				gu16v_Fun150CalDataEeCopy = gu16v_Fun150CalDataEe;
			}
			else
			{
				gu8v_CalModeIndex = 255;
				Beep(C_BP_NORMAL);
			}
		break;
		case 2://250mmHg		
			/*if(gu16v_90CalDataEe>(gu16v_30CalDataEe+300))//0.2V
			{
				gubv_WriteCalEe = 1;
			}
			else
			{
				gu8v_CalModeIndex = 255;
				Beep(C_BP_NORMAL);
			}*/
		break;
		case 3:
			//_wdtc = 0xff;//MUC reset 
		break;
	
		default:
		break;
	}
}

void	GetSensorCalAdcData_Task(void)
{

	gu16v_AbAdcZeroDataSum+=gu16v_ABAdcSensor;
	gu16v_FunAdcZeroDataSum+=gu16v_FunAdcSensor;
	gu8v_AbGetAdcZeroCnt++;
	if(gu8v_AbGetAdcZeroCnt>=8)
	{
		gu8v_AbGetAdcZeroCnt = 0;
		gu16v_AbAdcZeroDataSum >>= 3;
		gu16v_FunAdcZeroDataSum >>= 3;
		switch(gu8v_CalModeIndex)
		{
			case 0:
				gubv_GetZeroData = 0;
				gubv_ZeroUpdataEe1 = 1;
				gu16v_AbAdcZeroData = gu16v_AbAdcZeroDataSum;
				gu16v_FunAdcZeroData = gu16v_FunAdcZeroDataSum;
				gu8v_CalModeIndex = 1;
			break;
			case 1:
				gu16v_Ab150CalDataEe = gu16v_AbAdcZeroDataSum;
				gu16v_Fun150CalDataEe = gu16v_FunAdcZeroDataSum;
			break;
			case 2:
				//gu16v_90CalDataEe = gu16v_AdcZeroDataSum;
			break;
			case 3:
			break;
		}
		gu16v_AbAdcZeroDataSum = 0;
		gu16v_FunAdcZeroDataSum = 0;
	}

}	

void	FunPressure_Task(void)
{
	//unsigned char u8v_AbPressureMode;
	if(gubv_SensorAdUpdata) //180mS
	{
		gubv_SensorAdUpdata = 0;	
		
		if(gubv_CalMode)
		{
			GetSensorCalAdcData_Task();
		}
		else
		{
			if(gu8v_WorkMode==C_WORK_ON_MODE)
			{	
				if(!gu8v_AbFangQiTime)
				{
					/*if(!gubv_AbPressureFirstFull)
					{
						gu16v_AbSensroCmp = (4+8);//12KPa
					}
					else
					{
						gu16v_AbSensroCmp = (4+gu8v_PressureMode);
					}*/
					gu16v_AbSensroCmp = (4+gu8v_PressureMode);
					gu16v_AbSensroCmp = gu16v_AbSensroCmp*10;
					
					if(gu16v_ABAdcSensor>(gu16v_AbAdcZeroData+(gu16v_Ab7P5mmHgData*3)))
					{
						gu8v_AbPressureLowNorAdcCnt++;
						if(gu8v_AbPressureLowNorAdcCnt>=5)
						{
							gu8v_AbPressureLowNorAdcCnt = 0;
							gu16v_AbPressureLowErrTimeCnt = 0;
							gu16v_AbPressureLowErrTimeCmp = C_4_M;
							gubv_AbSensorErrAlarmMode = 0;
						}
					}
					else
					{
						gu8v_AbPressureLowNorAdcCnt = 0;
						if(gubv_1S_3)
						{
							gubv_1S_3 = 0;
							gu16v_AbPressureLowErrTimeCnt++;
							if(gu16v_AbPressureLowErrTimeCnt>=gu16v_AbPressureLowErrTimeCmp)
							{
								gu16v_AbPressureLowErrTimeCnt = 0;
								gubv_AbSensorErrAlarmMode = 1;
							}
						}
					}
					if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+10))
					{
						gu8v_AbSensorPressureCnt++;
						if(gu8v_AbSensorPressureCnt>=5)
						{
							gu8v_AbSensorPressureCnt = 0;
							gubv_AbMotoOff = 1;
							if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+80))
							{
								gu8v_AbFangQiTime = 250;//20*15=300
							}
							else if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+70))
							{
								gu8v_AbFangQiTime = 220;//20*15=300
							}
							else if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+60))
							{
								gu8v_AbFangQiTime = 190;//20*15=300
							}
							else if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+50))
							{
								gu8v_AbFangQiTime = 160;//20*15=300
							}
							else if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+40))
							{
								gu8v_AbFangQiTime = 130;//20*15=300
							}
							else if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+30))
							{
								gu8v_AbFangQiTime = 100;//20*15=300
							}
							else if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+20))
							{
								gu8v_AbFangQiTime = 70;//20*15=300
							}
							else
							{
								gu8v_AbFangQiTime = 40;
							}
							gubv_AbSensorFangQiEn = 1;
							goto abSensorPressureFull;
						}
					}
					else
					{
						if(!gubv_AbPressureFirstFull)
						{
							if(gu8v_AbNumDisValue>=120)
							{
								gu8v_12KpDebounce++;
								if(gu8v_12KpDebounce>=5)
								{
									gu8v_12KpDebounce = 0;
									if(gubv_StaticMode) gubv_StaticMode = 0;
									if(!gubv_AbPressureFirstFull)
									{
										gubv_AbPressureFirstFull = 1;
									}
								}
							}
							else
							{
								gu8v_12KpDebounce = 0;
							}
						}
						else
						{
							
							if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+5))
							{
								gu8v_AbMotoOnDebounce = 0;
								gu8v_AbMotoOffDebounce++;
								if(gu8v_AbMotoOffDebounce>=5)
								{
									gu8v_AbMotoOffDebounce = 0;
									gubv_AbMotoOff = 1;
								}
							}
							else
							{
								gu8v_AbMotoOffDebounce = 0;
								if(gu8v_AbNumDisValue<=gu16v_AbSensroCmp)
								{
									gu8v_AbMotoOnDebounce++;
									if(gu8v_AbMotoOnDebounce>=5)
									{
										gu8v_AbMotoOnDebounce = 0;
										gubv_AbMotoOff = 0;
									}
								}
								
								if(gu8v_AbNumDisValue>=(gu16v_AbSensroCmp+2))
								{
									gu8v_AbPressureNoFullAdcCnt = 0;
									gu8v_AbPressureFullAdcCnt++;
									if(gu8v_AbPressureFullAdcCnt>=5)//
									{
										gu8v_AbPressureFullAdcCnt = 0;
			
										abSensorPressureFull:
											gubv_AbPressureFull = 1;
											
									}
								}
								else
								{
									gu8v_AbSensorPressureCnt = 0;
									
									gu8v_AbPressureFullAdcCnt = 0;
									gu8v_AbSensorLowPwmCnt = 0;
									if(gu8v_AbNumDisValue<=(gu16v_AbSensroCmp-5))
									{
										gu8v_AbPressureNoFullAdcCnt++;
										if(gu8v_AbPressureNoFullAdcCnt>=5)
										{
											gu8v_AbPressureNoFullAdcCnt = 0;
											gubv_AbPressureFull = 0;
											gubv_AbSensorFangQiEn = 0;
											gu8v_AbFangQiTime = 0;
										}		
									}
								}
							}
						}
					}
					
					if(WorkModeFlag.byte)
					{
						if(!gubv_FunPressureFull)
						{
							gu8v_AbPwmDelay = C_DUTY_100P_L;// 
							gu8v_AbPwmDuty = C_DUTY_100P_H;//37*125uS=4.625mS		250mmHg
						}
						else
						{
							gu8v_AbPwmDelay = C_DUTY_60P_H;// 3.8mS 
							gu8v_AbPwmDuty = C_DUTY_60P_L;//5*125uS=625uS				110mmHg 20
						}
					}
					else
					{
						if(!gubv_AbPressureFull)
						{
							gu8v_AbPwmDelay = C_DUTY_100P_L;// 
							gu8v_AbPwmDuty = C_DUTY_100P_H;//37*125uS=4.625mS		250mmHg
						}
						else
						{
							gu8v_AbPwmDelay = C_DUTY_60P_H;// 3.8mS 
							gu8v_AbPwmDuty = C_DUTY_60P_L;//5*125uS=625uS				110mmHg 20
						}
					}
					
					gu8v_AbNumDisCurrentValue = gu8v_AbNumDisValue;
					/*if(gu8v_AbNumDisCurrentValue>=gu16v_AbSensroCmp+2)
					{
						gu8v_AbNumDisCurrentValue = gu16v_AbSensroCmp+2;
					}*/
				}
				if(WorkModeFlag.byte)
				{
					gu16v_FunSensroCmp = gu16v_FunAdcZeroData;
					if(gubv_FunPressureFirstFull)
					{
						if(gu8v_PressureMode<=3)	gu16v_FunSensroCmp += gu16v_Fun7P5mmHgData*7;
						else						gu16v_FunSensroCmp += gu16v_Fun7P5mmHgData*(4+gu8v_PressureMode);
					}
					else
					{
						gu16v_FunSensroCmp += gu16v_Fun7P5mmHgData*7;
					}
					if(!gubv_FunPressureFirstFull)
					{
						if(gu16v_FunAdcSensor>=gu16v_FunSensroCmp)
						{
							gu8v_7KpDebounce++;
							if(gu8v_7KpDebounce>=5)
							{
								gu8v_7KpDebounce = 0;
								gubv_StaticMode = gubv_StaticModeCopy;
								gu16v_JiaoTiTimeCnt = 0;
								gubv_FunPressureFirstFull = 1;
							}
						}
						else
						{
							gu8v_7KpDebounce = 0;
						}
					}
					else
					{
						if(gu16v_FunAdcSensor>=(gu16v_FunSensroCmp+(gu16v_Fun7P5mmHgData>>1)))
						{
							gu8v_FunMotoOnDebounce = 0;
							gu8v_FunMotoOffDebounce++;
							if(gu8v_FunMotoOffDebounce>=5)
							{
								gu8v_FunMotoOffDebounce = 0;
								gubv_FunMotoOff = 1;
							}
						}
						else
						{
							gu8v_FunMotoOffDebounce = 0;
							if(gu16v_FunAdcSensor<=gu16v_AbSensroCmp)
							{
								gu8v_FunMotoOnDebounce++;
								if(gu8v_FunMotoOnDebounce>=5)
								{
									gu8v_FunMotoOnDebounce = 0;
									gubv_FunMotoOff = 0;
								}
							}	
							if(gu16v_FunAdcSensor>=gu16v_FunSensroCmp)
							{
								gu8v_FunPressureLowAdcCnt = 0;
								gu8v_FunPressureFullAdcCnt++;
								if(gu8v_FunPressureFullAdcCnt>=5)//
								{
									gu8v_FunPressureFullAdcCnt = 0;
									gubv_FunPressureFull = 1;
									/*if(!gubv_FunPressureFirstFull)
									{
										gubv_StaticMode = gubv_StaticModeCopy;
										gu16v_JiaoTiTimeCnt = 0;
										gubv_FunPressureFirstFull = 1;
									}*/
								}
							}
							else
							{
								gu8v_FunPressureFullAdcCnt = 0;
								if(gu16v_FunAdcSensor<=(gu16v_FunSensroCmp-(gu16v_Fun7P5mmHgData>>1)))
								{
									gu8v_FunPressureLowAdcCnt++;
									if(gu8v_FunPressureLowAdcCnt>=5)//75,50
									{
										gu8v_FunPressureLowAdcCnt = 0;
										gubv_FunPressureFull = 0;
									}	
								}
							}
						}
					}
					if(!gubv_FunPressureFull)
					{
						gu8v_FunPwmDelay = C_DUTY_100P_L;// 
						gu8v_FunPwmDuty = C_DUTY_100P_H;//37*125uS=4.625mS		250mmHg
					}
					else
					{
						gu8v_FunPwmDelay = C_DUTY_60P_H;// 3.8mS 
						gu8v_FunPwmDuty = C_DUTY_60P_L;//5*125uS=625uS				110mmHg 20
					}
				}
			}
		}
	}	
}

void	Fun_IrRecKeyProcess(void)
{
	if(gubv_IrRecUpdata == 1)
	{
		gubv_IrRecUpdata = 0;
	
		/*if(gu8v_433RecValue[2]==C_IR_KEY_COPYID)
		{
			if(gu8v_RfIdCopyTime)
			{
				if(!gu8v_IrDelay)
				{
					gu16v_IdData.byte.byte1 = gu8v_433RecValue[0];
					gu16v_IdData.byte.byte2 = gu8v_433RecValue[1];
					gubv_WriteRfIdEe = 1;
					gu8v_433CopyIdData1[0] = 0;
					gu8v_433CopyIdData1[1] = 0;
					gu8v_433CopyIdData1[2] = 0;
					gu8v_IrDelay = C_IR_DELAY;
					gu8v_RfIdCopyTime = 0;
				}
			}
		}
		else
		{*/
			if(!gu8v_IrDelay)
			{
				//if((gu8v_433RecValue[0]==gu16v_IdData.byte.byte1)&&(gu8v_433RecValue[1]==gu16v_IdData.byte.byte2)) //
				//{
					if(gu8v_WorkMode==C_WORK_ON_MODE)
					{	
						switch(gu8v_433RecValue[2])
						{
						  case C_IR_KEY_ZUO_ZI:
						  	gubv_KeyShortQiBei = 1;
						  	gubv_KeyShortTaiTui = 1;
						  break;
						  case C_IR_KEY_AUTO:
						  	gubv_KeyShortAutoRL = 1;	
						  break;
						  case C_IR_KEY_LEFI_FANSHEN:
						  	gubv_KeyShortLeft = 1;
						  break;
						  case C_IR_KEY_RIGHT_FANSHEN:
						  	gubv_KeyShortRight = 1;
						  break;
						  case C_IR_KEY_QIBEI:
						  	gubv_KeyShortQiBei = 1;
						  break;
						  case C_IR_KEY_TAITUI:
						  	gubv_KeyShortTaiTui = 1;
						  break;
						  case C_IR_KEY_LOCK:
						  	gubv_KeyShortLock = 1;
						  break;
						  case C_IR_KEY_VOICE:
						  	gubv_KeyShortVoliceOff = 1;
						  break;
	
						}
					}
					else
					{
						
					}
					gu8v_IrDelay = C_IR_DELAY;
				//}
			}
		//}
		gu8v_433RecValue[0] = 0x00;	
		gu8v_433RecValue[1] = 0x00;
		gu8v_433RecValue[2] = 0x00;
	}
}
void	Fun_PowerOnMode(void)	
{
	DcfFlag1.byte = 0x03;//AB DCF ON
	if(!gu8v_PowerOnDelay)
	{
		Fun_InitWorkOffMode();
	}
	#if C_DEBUG_MODE
	#else
		FactoryMode_Task();
	#endif
}
void	Fun_WorkOffMode(void)
{
	if(gubv_KeyShortPower)
	{
		gubv_PowerStatus = 0;
		Beep(C_BP_NORMAL);
		Fun_InitWorkOnMode();
		Work_StatusRegInit();
		Work_SensorAdcRegInit();
		Init_TimerReg();
		Fun_GenVoicePluse(C_VOICE_POWER_ON);
	}
	WorkModeFlag.byte = 0x00;
	DcfFlag1.byte = 0x03;//AB DCF ON
	gu8v_AbFangQiTime = 0;
	gubv_AbSensorFangQiEn = 0;
}

void	Fun_EnterJiaotiMode(void)
{
	if(!WorkModeFlag.byte)
	{
		gu16v_JiaoTiTimeCnt = 0;
		if(gubv_StaticMode)
		{
		  //gu8v_PressureMode =	gu8v_PressureModeCopy;
		  gubv_StaticMode = gubv_StaticModeCopy;
		}
		else
		{
			
		}
	}
}

void	Fun_FirstEnterFunMode(void)
{
	if(!WorkModeFlag.byte)
	{
		//gu8v_PressureModeCopy = gu8v_PressureMode;
		gubv_StaticModeCopy = gubv_StaticMode;
		gubv_FunPressureFirstFull = 0;
		gubv_FunMotoOff = 0;
		gubv_AbMotoOff = 0;
	}
}


void Fun_KeyPressedProcess(void)
{
	if(!gubv_AbPressureFirstFull)
	{
		if(KeyFlag1.byte||KeyFlag2.byte)
		{
			if(KeyFlag1.byte)	Fun_GenVoicePluse(C_VOICE_WAIT_FUN_ON);
			KeyFlag1.byte = 0x00;
			KeyFlag2.byte = 0x00;
		}
	}
	if(gubv_KeyShortLock)
	{
		Init_TimerReg();
		gu8v_LockDelay60S = C_60S;
		gubv_LockStatus = ~gubv_LockStatus;
		if(gubv_LockStatus)	Fun_GenVoicePluse(C_VOICE_LOCK_ON);
		else				Fun_GenVoicePluse(C_VOICE_LOCK_OFF);
	}
	if(gubv_LockStatus)
	{
		if(!gubv_KeyShortAlermOff)
		{
			KeyFlag1.byte = 0x00;
			KeyFlag2.byte = 0x00;
			KeyFlag3.byte = 0x00;
		}
	}
	else
	{
		if(KeyFlag1.byte||KeyFlag2.byte||KeyFlag3.byte)
		{
			gu8v_LockDelay60S = C_60S;
		}
	}
	if(gubv_KeyShortVoliceOff)
	{
		gubv_VoliceOn = ~gubv_VoliceOn;
		if(gubv_VoliceOn)	
		{
			Fun_GenVoicePluse(C_VOICE_ON);
		}
		else				
		{
			Fun_GenVoicePluse(C_VOICE_OFF);	
		}
	}
	if((WorkModeFlag.byte)&&(!gubv_FunPressureFirstFull))
	{
		if(gubv_KeyShortPreAdd) gubv_KeyShortPreAdd = 0;
		if(gubv_KeyShortPreDec) gubv_KeyShortPreDec = 0;
	}
	if(gubv_KeyShortPreAdd)
	{
		Beep(C_BP_NORMAL);
		if(gu8v_PressureMode<4)	
		{
			gu8v_PressureMode++;
		}
		Fun_GenVoicePluse(C_VOICE_PRESSURE_UP);	
		gu8v_PreKeyDownDisTime = 50;
		Init_TimerReg();
	}
	if(gubv_KeyShortPreDec)
	{
		Beep(C_BP_NORMAL);
		if(gu8v_PressureMode)	
		{
			gu8v_PressureMode--;
		}
		Fun_GenVoicePluse(C_VOICE_PRESSURE_DOWN);
		gu8v_PreKeyDownDisTime = 50;
		Init_TimerReg();
	}
	if(gubv_KeyShortSleep)
	{
		if(gubv_FactoryTestMode)
		{
			Beep(C_BP_NORMAL);
		}
		else
		{
			if((WorkModeFlag.byte)&&(!gubv_FunPressureFirstFull))
			{
				Fun_GenVoicePluse(C_VOICE_BP_DIDI);
			}
			else
			{
				gubv_StaticMode = 1;
				Fun_GenVoicePluse(C_VOICE_SLEEP);	
				Beep(C_BP_NORMAL);
				gu8v_AbFangQiTime = 0;
				gubv_AbSensorFangQiEn = 0;
			}
		}
	}	
	if(gubv_KeyShort20M&&(!gubv_StaticMode))
	{
		gu8v_JiaoTiMode = 2;
		gu16v_JiaoTiTime = C_20_M;
		gu16v_JiaoTiTimeCmp = C_10_M;
		gu16v_JiaoTiTimeCnt = 0;
		Fun_GenVoicePluse(C_VOICE_20M);
	}
	if(gubv_KeyShort15M&&(!gubv_StaticMode))
	{
		gu8v_JiaoTiMode = 1;
		gu16v_JiaoTiTime = C_15_M;
		gu16v_JiaoTiTimeCmp = C_7_M_5;
		gu16v_JiaoTiTimeCnt = 0;
		Fun_GenVoicePluse(C_VOICE_15M);
	}
	if(gubv_KeyShort10M&&(!gubv_StaticMode))
	{
		gu8v_JiaoTiMode = 0;
		gu16v_JiaoTiTime = C_10_M;
		gu16v_JiaoTiTimeCmp = C_5_M;
		gu16v_JiaoTiTimeCnt = 0;
		Fun_GenVoicePluse(C_VOICE_10M);
	}
	if(gubv_KeyShortAutoRL)
	{
		Fun_FirstEnterFunMode();
		gubv_AutoMode = ~gubv_AutoMode;
		if(gubv_AutoMode)
		{
			Fun_GenVoicePluse(C_VOICE_AUTO_FANSHENG_ON);
			gubv_StaticMode = 1;
			//gu8v_PressureMode = 4;//8KPA
		}
		else
		{
			Fun_GenVoicePluse(C_VOICE_AUTO_FANSHENG_OFF);
			Fun_EnterJiaotiMode();
		}
		gubv_QiBeiMode = 0;
		gubv_DcfLeftFanShenMode = 0;
		gubv_DcfRightFanShenMode = 0;
		gubv_TaituiMode = 0;

		gu16v_AutoModeCycle = 0;
		
		Work_SensorAdcRegInit();
		Beep(C_BP_NORMAL);
	}	
	if(gubv_KeyShortQiBei)
	{
		Fun_FirstEnterFunMode();
		gubv_QiBeiMode =~gubv_QiBeiMode;
		if(gubv_QiBeiMode)
		{
			Fun_GenVoicePluse(C_VOICE_QB_ON);
			gubv_StaticMode = 1;
			//gu8v_PressureMode = 4;//8KPA
		}
		else
		{
			Fun_GenVoicePluse(C_VOICE_QB_OFF);
			Fun_EnterJiaotiMode();
		}
		gubv_DcfLeftFanShenMode = 0;
		gubv_DcfRightFanShenMode = 0;
		gubv_AutoMode = 0;
		Work_SensorAdcRegInit();
		Beep(C_BP_NORMAL);
	}	
	if(gubv_KeyShortAlermOff)
	{
		if(gubv_FactoryTestMode)
		{
			Beep(C_BP_NORMAL);
			Fun_GenVoicePluse(C_VOICE_ALARM_OFF);
		}
		if(gubv_AbSensorErrAlarmMode||gubv_FunSensorErrAlarmMode)
		{
			gubv_AbSensorErrAlarmMode = 0;
			gubv_FunSensorErrAlarmMode = 0;
			
			gu16v_AbPressureLowErrTimeCnt = 0;
			gu16v_FunPressureLowErrTimeCnt = 0;
						
			Fun_GenVoicePluse(C_VOICE_ALARM_OFF);	
		}
	}
	if(gubv_KeyShortLeft)
	{
		Fun_FirstEnterFunMode();
		gubv_DcfLeftFanShenMode = ~gubv_DcfLeftFanShenMode;
		if(gubv_DcfLeftFanShenMode)
		{
			Fun_GenVoicePluse(C_VOICE_LEFT_FANSHENG_ON);
			gubv_StaticMode = 1;
			//gu8v_PressureMode = 4;//8KPA
		}
		else
		{
			Fun_GenVoicePluse(C_VOICE_LEFT_FANSHENG_OFF);
			Fun_EnterJiaotiMode();
		}
		gubv_QiBeiMode = 0;
		gubv_DcfRightFanShenMode = 0;
		gubv_TaituiMode = 0;
		gubv_AutoMode = 0;
		//WorkModeFlag.byte &= 0x10;
		Work_SensorAdcRegInit();
		Beep(C_BP_NORMAL);

	}	
	if(gubv_KeyShortRight)
	{
		Fun_FirstEnterFunMode();
		gubv_DcfRightFanShenMode = ~gubv_DcfRightFanShenMode;
		if(gubv_DcfRightFanShenMode)
		{
			Fun_GenVoicePluse(C_VOICE_RIGHT_FANSHENG_ON);
			gubv_StaticMode = 1;
			//gu8v_PressureMode = 4;//8KPA
		}
		else
		{
			Fun_GenVoicePluse(C_VOICE_RIGHT_FANSHENG_OFF);
			Fun_EnterJiaotiMode();
		}
		gubv_QiBeiMode = 0;
		gubv_DcfLeftFanShenMode = 0;
		gubv_TaituiMode = 0;
		gubv_AutoMode = 0;

		//WorkModeFlag.byte &= 0x20;
		Work_SensorAdcRegInit();
		Beep(C_BP_NORMAL);
	}		
	if(gubv_KeyShortTaiTui)
	{
		Fun_FirstEnterFunMode();
		gubv_TaituiMode = ~gubv_TaituiMode;
		if(gubv_TaituiMode)
		{
			Fun_GenVoicePluse(C_VOICE_LEG_ON);
			gubv_StaticMode = 1;
			//gu8v_PressureMode = 4;//8KPA
		}
		else
		{
			Fun_GenVoicePluse(C_VOICE_LEG_OFF);
			Fun_EnterJiaotiMode();
		}
		gubv_DcfLeftFanShenMode = 0;
		gubv_DcfRightFanShenMode = 0;
		gubv_AutoMode = 0;

		Work_SensorAdcRegInit();
		Beep(C_BP_NORMAL);

	}
	if(gubv_KeyShortAL)
	{
		if((WorkModeFlag.byte)&&(!gubv_FunPressureFirstFull))
		{
			Fun_GenVoicePluse(C_VOICE_BP_DIDI);
		}
		else
		{
			if(!gubv_AbPressureFirstFull)
			{
				Fun_GenVoicePluse(C_VOICE_BP_DIDI);
			}
			else
			{
				if(gubv_StaticMode)
				{
					gu8v_JiaoTiMode = 0;
				}
				Beep(C_BP_NORMAL);
				gubv_StaticMode = 0;
				Fun_GenVoicePluse(C_VOICE_AL);
				gu16v_JiaoTiTimeCnt = 0;
				gu8v_AbFangQiTime = 0;
				gubv_AbSensorFangQiEn = 0;
			}
		}
	}
	if(gubv_KeyShortPower)
	{
		gubv_PowerStatus = 1;
		Beep(C_BP_NORMAL);
		gu8v_WorkMode = C_WORK_OFF_MODE;
		Fun_GenVoicePluse(C_VOICE_POWER_OFF);
	}
}
void	Fun_JiaoTiModeProcess(void)
{
	//if((!gubv_FunPressureFull)&&(WorkModeFlag.byte))
	if((!gubv_FunPressureFirstFull)&&(WorkModeFlag.byte))
	{
		gubv_DcfA = 1;
		gubv_DcfB = 1;
	}
	else
	{
		if(gubv_StaticMode)
		{
			gu16v_JiaoTiTimeCnt = 0;
			gubv_DcfA = 1;
			gubv_DcfB = 1;
		}
		else
		{
			if(gubv_1S_2)
			{
				gubv_1S_2 = 0;
				gu16v_JiaoTiTimeCnt++;
				
				if(gu16v_JiaoTiTimeCnt>=gu16v_JiaoTiTime)
				{
					gu16v_JiaoTiTimeCnt = 0;
				}
				if(gu16v_JiaoTiTimeCnt<=(gu16v_JiaoTiTimeCmp-10))
				{
					gubv_DcfA = 1;
					gubv_DcfB = 0;
				}
				else if(gu16v_JiaoTiTimeCnt<=gu16v_JiaoTiTimeCmp)
				{
					gubv_DcfA = 0;
					gubv_DcfB = 0;
				}
				else if(gu16v_JiaoTiTimeCnt<=(gu16v_JiaoTiTime-10))
				{
					gubv_DcfB = 1;
					gubv_DcfA = 0;
				}
				else 
				{
					gubv_DcfB = 0;
					gubv_DcfA = 0;
				}
			}
		}
	}
}
void	Fun_WorkOnMode(void)
{
	Fun_KeyPressedProcess();
	if(gubv_1S)
	{
		gubv_1S = 0;
		if(gubv_AutoMode)
		{
			gu16v_AutoModeCycle++;
			if(gu16v_AutoModeCycle>=C_AutoModeCycle)
			{
				gu16v_AutoModeCycle = 0;
			}
			if(gu16v_AutoModeCycle<C_AutoModeZuoON)
			{
				gubv_AutoLeftFanShenMode = 1;
			}
			else if(gu16v_AutoModeCycle<C_AutoModeZuoOFF)
			{
				gubv_AutoLeftFanShenMode = 0;
			}
			else if(gu16v_AutoModeCycle<C_AutoModeYouON)
			{
				gubv_AutoRightFanShenMode = 1;
			}
			else
			{
				gubv_AutoRightFanShenMode = 0;
			}
		}
		if(gubv_AbSensorErrAlarmMode||gubv_FunSensorErrAlarmMode)
		{
			Fun_GenVoicePluse(C_VOICE_BP_DIDI);
		}
	}
	Fun_JiaoTiModeProcess();
	if(!gubv_AutoMode)
	{
		gubv_AutoLeftFanShenMode = 0;
		gubv_AutoRightFanShenMode = 0;
	}
	if(gubv_QiBeiMode)
	{
		gubv_DcfQiBei = 1;
	}
	else
	{
		gubv_DcfQiBei = 0;
	}
	if(gubv_DcfLeftFanShenMode||gubv_AutoLeftFanShenMode)
	{
		gubv_DcfLeftFanShen = 1;
	}
	else
	{
		gubv_DcfLeftFanShen = 0;
	}
	if(gubv_DcfRightFanShenMode||gubv_AutoRightFanShenMode)
	{
		gubv_DcfRightFanShen = 1;
	}
	else
	{
		gubv_DcfRightFanShen = 0;
	}
	if(gubv_TaituiMode)
	{
		gubv_DcfTaiTui = 1;
	}
	else
	{
		gubv_DcfTaiTui = 0;
	}
	
}
void	Fun_IoConProcess(void)
{
	if(gubv_FactoryTestMode)
	{
		if(gubv_CalMode)
		{
			P_DCF_QiBei = C_DCF_OFF;
			P_DCF_RightFanShen = C_DCF_OFF;
			P_DCF_LeftFanShen = C_DCF_OFF;
			P_DCF_TaiTui = C_DCF_OFF;
			P_DCF_A = C_DCF_OFF;
			P_DCF_B = C_DCF_OFF;
		}
		else
		{
			if(gubv_500mS_Flash) 
			{
				P_DCF_QiBei = C_DCF_ON;
				P_DCF_RightFanShen = C_DCF_ON;
				P_DCF_LeftFanShen = C_DCF_ON;
				P_DCF_TaiTui = C_DCF_ON;
				P_DCF_A = C_DCF_ON;
				P_DCF_B = C_DCF_ON;
			}
			else
			{
				P_DCF_QiBei = C_DCF_OFF;
				P_DCF_RightFanShen = C_DCF_OFF;
				P_DCF_LeftFanShen = C_DCF_OFF;
				P_DCF_TaiTui = C_DCF_OFF;
				P_DCF_A = C_DCF_OFF;
				P_DCF_B = C_DCF_OFF;
			}
		}
	}
	else
	{
		if(gu8v_AbFangQiTime>=1)
		{
			P_DCF_A = C_AB_DCF_OFF;
			P_DCF_B = C_AB_DCF_OFF;
		}
		else
		{
			if(gubv_DcfA)		
			{
				P_DCF_A = C_AB_DCF_ON;
			}
			else				
			{
				P_DCF_A = C_AB_DCF_OFF;
			}
			if(gubv_DcfB)		
			{
				P_DCF_B = C_AB_DCF_ON;
			}
			else				
			{
				P_DCF_B = C_AB_DCF_OFF;
			}
		}
		if(gubv_DcfQiBei)				P_DCF_QiBei = C_DCF_ON;
		else							P_DCF_QiBei = C_DCF_OFF;
		if(gubv_DcfRightFanShen)		P_DCF_RightFanShen = C_DCF_ON;
		else							P_DCF_RightFanShen = C_DCF_OFF;
		if(gubv_DcfLeftFanShen)			P_DCF_LeftFanShen = C_DCF_ON;
		else							P_DCF_LeftFanShen = C_DCF_OFF;
		if(gubv_DcfTaiTui)				P_DCF_TaiTui = C_DCF_ON;
		else							P_DCF_TaiTui = C_DCF_OFF;
	}
}

void	Fun_PublicProcess(void)
{
	KeyFlag1.byte = 0x00;
	KeyFlag2.byte = 0x00;
	KeyFlag3.byte = 0x00;
	
	if(gubv_1S_1)
	{
		gubv_1S_1 = 0;
		if(gubv_WriteRfIdEe)
		{
			if(EEPROM_WriteBytes(C_RF_ID_EE_ADD1,gu16v_IdData.u16byteS))
			{
				if(EEPROM_WriteBytes(C_RF_ID_EE_ADD2,gu16v_IdData.u16byteS))
				{
					gubv_WriteRfIdEe = 0;
					Beep(C_BP_ALARM);
				}
			}
		}
		if(gubv_WriteCalEe)
		{
			if(EEPROM_WriteBytes(C_CAL_DATA1_EE1_ADD1,gu16v_Ab150CalDataEeCopy))
			{
				if(EEPROM_WriteBytes(C_CAL_DATA1_EE2_ADD1,gu16v_Ab150CalDataEeCopy))
				{
					if(EEPROM_WriteBytes(C_CAL_DATA2_EE1_ADD1,gu16v_Fun150CalDataEeCopy))
					{
						if(EEPROM_WriteBytes(C_CAL_DATA2_EE2_ADD1,gu16v_Fun150CalDataEeCopy))
						{
							gubv_WriteCalEe = 0;
							gu8v_CalModeIndex = 3;//
							gu16v_Ab7P5mmHgData = (gu16v_Ab150CalDataEe-gu16v_AbAdcZeroData)/20;
							gu16v_Fun7P5mmHgData = (gu16v_Fun150CalDataEe-gu16v_FunAdcZeroData)/20;
							Beep(C_BP_NORMAL);
						}
					}
				}
			}
		}
		if(gubv_ZeroUpdataEe1)
		{
			if(EEPROM_WriteBytes(C_ZERO_DATA1_EE1_ADD1,gu16v_AbAdcZeroData))
			{
				if(EEPROM_WriteBytes(C_ZERO_DATA1_EE2_ADD1,gu16v_AbAdcZeroData))
				{
					if(EEPROM_WriteBytes(C_ZERO_DATA2_EE1_ADD1,gu16v_FunAdcZeroData))
					{
						if(EEPROM_WriteBytes(C_ZERO_DATA2_EE2_ADD1,gu16v_FunAdcZeroData))
						{
							gubv_ZeroUpdataEe1 = 0;
						}
					}
				}
			}
		}
		if(gu8v_PowerOnDelay<=10)
		{
			if(gubv_PowerOnReadEe)
			{
				if(EEPROM_ReadBytes(C_ZERO_DATA1_EE1_ADD1))
				{
				  	gu16v_AbAdcZeroData = gu16v_EeTemp;
					if(EEPROM_ReadBytes(C_CAL_DATA1_EE1_ADD1))
					{
						gu16v_Ab150CalDataEe = gu16v_EeTemp;
						
						if(EEPROM_ReadBytes(C_ZERO_DATA2_EE1_ADD1))
						{
						  	gu16v_FunAdcZeroData = gu16v_EeTemp;
							if(EEPROM_ReadBytes(C_CAL_DATA2_EE1_ADD1))
							{
								gu16v_Fun150CalDataEe = gu16v_EeTemp;
								gu16v_Ab7P5mmHgData = (gu16v_Ab150CalDataEe-gu16v_AbAdcZeroData)/20;
								gu16v_Fun7P5mmHgData = (gu16v_Fun150CalDataEe-gu16v_FunAdcZeroData)/20;
								if(EEPROM_ReadBytes(C_RF_ID_EE_ADD1))
								{
									gu16v_IdData.u16byteS = gu16v_EeTemp;
									gubv_PowerOnReadEe = 0;
									
								}
							}
						}
					}
				}
			}
		}
	}
}

////===============================================================
////void Function_Task (void)
////===============================================================		
void Function_Task (void)
{
	Fun_IrRecKeyProcess();
	switch(gu8v_WorkMode)
	{
		case C_POWER_ON_MODE:
			Fun_PowerOnMode();	
		break;	
		case C_WORK_OFF_MODE:
			Fun_WorkOffMode();
		break;
		case C_WORK_ON_MODE:
			Fun_WorkOnMode();
		break;	
	}
	Fun_PublicProcess();
}


