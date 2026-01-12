#include    "USER_PROGRAM.INC"

//#include    "USER_PROGRAM.H"  

#include	"..\Source\MyDefine.h"
#include	"..\Source\Variants.h"
#include "drv_iouart_tx.h"
#include    "drv_tm1652.h"

extern	void  	Sys_Init(void);
extern	void 	User_Init(void);
extern	void 	Display_Task (void);
extern	void 	Beep (unsigned char bp_type);
extern	void 	Beep_Task (void);
extern	void 	ADC_Task (void);
extern	void 	Key_Task (void);
extern	void 	Function_Task(void);
extern	void 	Time_Base(void);
extern	void 	Fun_IrRecKeyProcess(void);
extern	void 	Fun_PowerOnMode(void);	
extern	void 	Fun_WorkOffMode(void);
extern	void 	Fun_WorkOnMode(void);
extern	void 	Fun_PublicProcess(void);
extern	void 	Uart0_Task(void);
extern	void 	Ac_lostDel(void);
extern	void 	FunPressure_Task(void);
extern	void	Fun_IoConProcess(void);
              
//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_INITIAL()
{
	Sys_Init();
	User_Init();
	//Beep(C_BP_NORMAL);
}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM()
{
	#if 1
	if(gubv_5mS)
	{
		gubv_5mS = 0;
		gu16v_KeyBuffer = 0x0000;
		GET_KEY_BITMAP();
		gu8v_KeyBuf1 = DATA_BUF[0];
		gu8v_KeyBuf2 = DATA_BUF[1];
		gu8v_KeyBuf3 = DATA_BUF[2];
		Key_Task();
		//Beep_Task();
		ADC_Task();
        drv_tm1652_task();
        
	}
	if(gubv_10mS)
	{
		gubv_10mS = 0;
		Function_Task();
		Fun_IoConProcess();
		FunPressure_Task();	
	}	
	if(gubv_50mS)
	{
		gubv_50mS = 0;
		Display_Task();	
	}
	if(gubv_100mS)
	{
		gubv_100mS = 0;
		Time_Base();
	}
	#endif
    iouart_startscan();
    GCC_CLRWDT();
}


void USER_PROGRAM_HALT_PREPARE()
{
	
}

void USER_PROGRAM_HALT_WAKEUP()
{
	
}

void USER_PROGRAM_RETURN_MAIN()
{
	
}