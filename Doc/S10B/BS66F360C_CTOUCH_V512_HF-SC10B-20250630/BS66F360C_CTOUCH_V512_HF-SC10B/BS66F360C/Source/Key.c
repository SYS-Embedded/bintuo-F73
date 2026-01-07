//#include <BS86D12C.H>

#include	"Key.h"

void FactoryMode_Task(void)
{
	if(!P_FACTORY_TEST)
	{
		gu8v_FactoryDebounce++;
		if(gu8v_FactoryDebounce>=50)
		{
			gu8v_FactoryDebounce = 0;
			gubv_FactoryTestMode = 1;
			gu8v_WorkMode = C_WORK_ON_MODE;
			gu8v_PowerOnDelay = 0;
			Init_TimerReg();
		}
	}
	else
	{
		gu8v_FactoryDebounce = 0;
	}
}

////===============================================================
////void Key_Task (void)
////===============================================================
void Key_Task (void)
{	
	if(!P_KEY_POWER)	gu8v_KeyBuf3=C_KEYVALUE_POWER;
	if(gu8v_KeyBuf1||gu8v_KeyBuf2||gu8v_KeyBuf3)
	{
		P_TEST =~P_TEST;
		gu8v_KeyOffDebounce = 0;
		gu8v_KeyDebounce++;
		if(gu8v_KeyDebounce>=5)
		{
			gu8v_KeyDebounce = 0;
			if(!gubv_KeyPressed)
			{
				gubv_KeyPressed = 1;
				gu8v_KeyLongDelay = 15;			//100mS*30=3000mS,3S
				gubv_KeyLongPressed=0;
				
				if(gu8v_KeyBuf1&C_KEYVALUE_20M)
				{
					gubv_KeyShort20M = 1;
				}
				else if(gu8v_KeyBuf1&C_KEYVALUE_15M)
				{
					gubv_KeyShort15M = 1;
				}
				else if(gu8v_KeyBuf1&C_KEYVALUE_10M)
				{
					gubv_KeyShort10M = 1;
				}
				else if(gu8v_KeyBuf1&C_KEYVALUE_QiBei)
				{
					gubv_KeyShortQiBei = 1;
				}
				else if(gu8v_KeyBuf1&C_KEYVALUE_TAITUI)
				{
					gubv_KeyShortTaiTui = 1;
				}
				else if(gu8v_KeyBuf1&C_KEYVALUE_LEFT)
				{
					gubv_KeyShortLeft = 1;
				}
				else if(gu8v_KeyBuf2&C_KEYVALUE_RIGHT)
				{
					gubv_KeyShortRight = 1;
				}
				else if(gu8v_KeyBuf2&C_KEYVALUE_AL)
				{
					gubv_KeyShortAL = 1;
				}
				else if(gu8v_KeyBuf2&C_KEYVALUE_SLEEP)
				{
					gubv_KeyShortSleep = 1;
				}
				else if(gu8v_KeyBuf2&C_KEYVALUE_AUTO_RL)
				{
					gubv_KeyShortAutoRL = 1;
				}
				else if(gu8v_KeyBuf3&C_KEYVALUE_NORMAL_PRE)
				{
					gubv_KeyShortNorPre = 1;
				}
				else if(gu8v_KeyBuf3&C_KEYVALUE_LOW_PRE)
				{
					gubv_KeyShortLowPre = 1;
				}
				else if(gu8v_KeyBuf3&C_KEYVALUE_ALARM)
				{
					gubv_KeyShortAlermOff  = 1;
				}
				else 
				{
					if(gu8v_KeyBuf2&C_KEYVALUE_VOLICE_OFF)
					{
						gubv_KeyShortVoliceOff = 1;
					}
					else if(gu8v_KeyBuf3&C_KEYVALUE_PRE_ADD)
					{
						if(gubv_CalMode)
						{
							Fun_CalModeProcess();
						}
						gubv_KeyShortPreAdd  = 1;
					}
					else if(gu8v_KeyBuf3&C_KEYVALUE_PRE_DEC)
					{
						if(gubv_FactoryTestMode&&(!gubv_CalMode))
						{
							gubv_CalMode = 1;
							gu8v_CalModeIndex = 0;
							gubv_GetZeroData = 1;
							gu8v_AbGetAdcZeroCnt = 0;
						}
						gubv_KeyShortPreDec = 1;
					}
					else if(gu8v_KeyBuf3&C_KEYVALUE_POWER)
					{
						gubv_KeyShortPower  = 1;
					}
				}
			}
			else
			{
				if((!gu8v_KeyLongDelay) && (!gubv_KeyLongPressed))
				{
					gu8v_KeyLongDelay = 15;			//100mS*30=3000mS,3S
					gubv_KeyLongPressed = 1;
					if(gu8v_KeyBuf3&C_KEYVALUE_LOCK)
					{
						gubv_KeyShortLock = 1;
					}
				}
			}
		}
	}
	else
	{
		gu8v_KeyDebounce = 0;
		gu8v_KeyOffDebounce++;
		if(gu8v_KeyOffDebounce>=5)
		{
			gu8v_KeyOffDebounce = 0;	
			gubv_KeyPressed = 0;
			gu8v_KeyDebounce = 0;
			gubv_KeyLongPressed = 0;	
		}
	}
}
