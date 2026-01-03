#include	"Beep.h"

////===============================================================
////void Beep_Task (void) 5mS执行一次
////===============================================================
void Beep_Task (void)
{
	switch(gu8v_BeepType)
	{
		case C_BP_WORK_ON:
		break;
		case C_BP_WORK_OFF:
			if(gu8v_BeepTime<=30) gubv_BeepOn = 0;
		break;
		case C_BP_NORMAL:
			if(gu8v_BeepTime<=30) gubv_BeepOn = 0;
		break;
		case C_BP_ALARM:
			if(gu8v_BeepTime<=25) gubv_BeepOn = 0;
		break;
		case C_BP_ERROR:
			gu8v_BeepTime = 100;			//50*10mS=500ms
		break;
		default:
		break;
	}
	if(!gu8v_BeepTime)
	{
		if(gu8v_BeepCnt)
		{
			gu8v_BeepCnt--;
			if(gu8v_BeepCnt)
			{
				gubv_BeepOn = 1;
				if(gu8v_BeepType==C_BP_ALARM)
				{
					gu8v_BeepTime = 50;//50*10mS=500ms
				}
				else
				{
					gu8v_BeepTime = 50;//50*10mS=500ms
				}
			}
			else
			{
			
			}
		}
	}
}

////===============================================================
////void Beep (void)
////===============================================================
void Beep (unsigned char bp_type)
{
	gubv_BeepOn = 1;
	gu8v_BeepCnt = 1;
	gu8v_BeepTime = 50;			//50*10mS=500ms
	gu8v_BeepType = bp_type;
	switch(bp_type)
	{
		case C_BP_WORK_ON:
		break;
		case C_BP_WORK_OFF:
			gu8v_BeepCnt = 5;//响5下
		break;
		case C_BP_NORMAL:
		break;
		case C_BP_ALARM:
			gu8v_BeepCnt = 3;//响2下
			gu8v_BeepTime = 50;			//20*10mS=200ms
		break;
		case C_BP_ION_OFF:
		break;
		case C_BP_ERROR:
			gu8v_BeepTime = 100;			//50*10mS=500ms
		break;
		
		default:
		break;
	}
}
