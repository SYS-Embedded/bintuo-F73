
#include "Initial.h"
#include "drv_tm1652.h"
/**************************************************
**************************************************/
/**************************************************
*�������ƣ�void  Sys_Init(void) 
*�������ܣ�ϵͳ��ʼ��
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void  Sys_Init(void)
{	
	_pf =   0b00100000;
	_pfc =  0b00100000;
	_pfpu = 0b00100000;
	
	_pe =   0b00000000;
	_pec =  0b00000000;
	_pepu = 0b00000000;
	
	_pac =  0b00011001;
	_pa =   0b00011001;
	_papu = 0b00011001;

	_pbc =  0b00001111;
	_pb =   0b00001111;
	_pbpu = 0b00001100;
	
	_pc =   0b00000000;
	_pcc =  0b00000000;
	_pcpu = 0b00000000;
	
	_pd =   0b00000000;
	_pdc =  0b00000000;
	_pdpu = 0b00000000;
	
	//_lvrc=0b00110011;//��2.55V
	_lvrc=0b01010101;//��2.1V
	/*
		Bit 7~0 LVS7~LVS0�� LVR ��ѹѡ��
			01010101�� 2.1V
			00110011�� 2.55V
			10011001�� 3.15V
			10101010�� 3.8V
	*/
	_lvdc=0b00011001;//��2.2V
	/*
		Bit 7~6 δ���壬��Ϊ��0��
		Bit 5 LVDO��LVD �����־�?
			0��δ��⵽�͵��?
			1����⵽�͵��?
		Bit 4 LVDEN���͵�ѹ������λ
			0������
			1��ʹ��
		Bit 3 VBGEN��Bandgap ��ѹ��������?
			0������
			1��ʹ��
		ע�⣬�� LVD �� LVR ʹ�ܻ� VBGEN ��λʱ��Bandgap ���Զ�ʹ�ܡ�
			Bit 2~0 VLVD2~VLVD0��ѡ�� LVD ��ѹλ
			000��2.0V
			001��2.2V
			010��2.4V
			011��2.7V
			100��3.0V
			101��3.3V
			110��3.6V
			111��4.0V
	*/
	_wdtc=0b01010111;
	/*
		Bit 7~3 WE4~WE0�� WDT ���ܿ���
		01010 �� 10101��ʹ��
		����ֵ����Ƭ����λ
		������ڲ����Ļ�������ʹ��Щλ��Ϊ����ֵ����Ƭ������λ����λ��������?
		�� tSRESET �ӳ�ʱ�����?CTRL �Ĵ����� WRF λ����Ϊ�� 1����
		Bit 2~0 WS2~WS0�� WDT �������ѡ���?
		000�� 28/fSUB
		001�� 210/fSUB
		010�� 212/fSUB
		011�� 214/fSUB
		100�� 215/fSUB
		101�� 216/fSUB
		110�� 217/fSUB
		111�� 218/fSUB
	*/
	_ifs0=0b00000000;
	/*
		Bit 7~6 δ���壬��Ϊ��0��
		Bit 5~4 IFS05~IFS04��SCS ����Դ����ѡ��
			00��PA2
			01��PA3
			10��PA2
			11��PA3
		Bit 3~2 IFS03~IFS02��PTPI ����Դ����ѡ��
			00��PB2
			01��PB4
			10��PB2
			11��PB4
		Bit 1~0 IFS01~IFS00��STPI ����Դ����ѡ��
			00��PE2
			01��PE3
			10��PE2
			11��PE3
	*/
	_ifs1=0b00000000;
	/*
		Bit 7~6 δ���壬��Ϊ��0��
		Bit 5~4 IFS15~ IFS14��SDI/SDA ����Դ����ѡ��
			00��PB0
			01��PA5
			10��PB0
			11��PA5
		Bit 3~2 IFS13~ IFS12��SCK/SCL ����Դ����ѡ��
			00��PB1
			01��PB1
			10��PA1
			11��PA1
		Bit 1~0 IFS11~ IFS10��RX ����Դ����ѡ��
			00��PB3
			01��PB3
			10��PA1
			11��PA1
	*/
	_pas0=0b00000000;
	_pas1=0b00000000;
	_pbs0=0b00001111;//AN1,AN0
	/*
		Bit 7~6 PBS07~PBS06��PB3 ���Ź��ù���ѡ��
			00��PB3
			01��RX
			10��PB3
			11��AN3
		Bit 5~4 PBS05~PBS04��PB2 ���Ź��ù���ѡ��
			00��PB2/PTPI
			01��TX
			10��PTP
			11��AN2
		Bit 3~2 PBS03~PBS02��PB1 ���Ź��ù���ѡ��
			00��PB1
			01��SCK/SCL
			10��PB1
			11��AN1
		Bit 1~0 PBS01~PBS00��PB0 ���Ź��ù���ѡ��
			00��PB0
			01��SDI/SDA
			10��VREF
			11��AN0
	*/
	_pbs1=0b00000000;
	_pcs0=0b00000000;
	_pcs1=0b00000000;
	_pds0=0b00000000;
	_pds1=0b00000000;
	_pes0=0b00000000;
	_pes1=0b00000000;
	_pfs0=0b00000000;
	_pfs1=0b00000000;
	_pmps=0b00000000;
	_pans=0b00000000;
	/*
		Bit 7 PANS7��PA7 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 6 PANS6��PA6 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 5 PANS5��PA5 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 4~2 δ���壬��Ϊ��0��
		Bit 1 PANS1��PA1 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 0 δ���壬��Ϊ��0
	*/
	_pens=0b00000000;
	/*
		Bit 7 PENS7��PE7 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 6 PENS6��PE6 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 5~0 δ���壬��Ϊ��0��
	*/
	_pfns=0b00000000;
	/*
		Bit 7~6 δ���壬��Ϊ��0��
		Bit 5 PFNS5��PF5 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 4 PFNS4��PF4 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 3 PFNS3��PF3 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 2 PFNS2��PF2 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 1 PFNS1��PF1 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
		Bit 0 PFNS0��PF0 �����ѡ���?( NMOS ���� )
			0��Level 0 ( ��С )
			1��Level 1 ( ���?)
	*/
	_sadc0 = C_ADC_CH_AB;
	/*
	Bit 7 START������ A/D ת��λ
		0��1��0������ A/D ת��
		��λ���ڳ�ʼ�� A/D ת�����̡�ͨ����λΪ�ͣ��������Ϊ���ٱ����㣬����?
		ʼ�� A/D ת�����̡�
	Bit 6 ADBZ��A/D ת��æµ��־λ
		0��A/D ת��������δ��ʼת��
		1��A/D ת����
		��λ���ڱ��� A/D ת�������Ƿ���ɡ���?START λ�ɵͱ�Ϊ���ٱ�Ϊ��ʱ��
		ADBZ λΪ�ߣ����� A/D ת���ѳ�ʼ����A/D ת�������󣬴�λ�����㡣
	Bit 5 ADCEN��A/D ת����ʹ�� / ���ܿ���λ
		0������
		1��ʹ��
		��λ���� A/D �ڲ����ܡ���λ���ø߽�ʹ�� A/D ת�����������λ��Ϊ��?
		���ر� A/D ת�����Խ��͹��ġ��� A/D ת�������ܳ���ʱ��A/D ���ݼĴ���
		SADOH �� SADOL �����ݽ������䡣
	Bit 4 ADRFS��A/D ת�����ݸ�ʽѡ��λ
		0��A/D ת�����ݸ�ʽ �� SADOH=D[11:4]; SADOL=D[3:0]
		1��A/D ת�����ݸ�ʽ �� SADOH=D[11:8]; SADOL=D[7:0]
		��λ���ƴ��������?A/D ���ݼĴ����е� 12 λ A/D ת������ĸ�ʽ��ϸ�ڷ�?
		����ο�?A/D ת�������ݼĴ����½ڡ�
	Bit 3~0 SACS3~SACS0��A/D ת�����ⲿ����ͨ��ѡ��λ
		0000��AN0
		0001��AN1
		0010��AN2
		0011��AN3
		0100��AN4
		0101��AN5
		0110��AN6
		0111��AN7
		1xxx����ͨ�������븡��
	*/
	_sadc1=0b00001011; //vdd,fsys/8
	/*
		Bit 7~5 SAINS2~SAINS0��A/D ת���������ź�ѡ��λ
			000���ⲿ��Դ �C �ⲿģ��ͨ������ ANn
			001���ڲ���Դ �C �ڲ� Bandgap �ο���ѹ VBG
			010~100���ڲ���Դ �C �������ӵ�
			101~111���ⲿ��Դ �C �ⲿģ��ͨ������ ANn
			�� SAINS λ������Ϊ��001����ѡ���ڲ�ģ���źŽ���ת��ʱ�����ر�С�ġ�
			��ѡ��ת���ڲ�ģ���źţ�SACS λ�α�������Ϊ��1xxx���������ⲿͨ������
			�����ڲ�ģ���ź����ӣ������²���Ԥ�ڵĺ����?
		Bit 4~3 SAVRS1~SAVRS0��A/D ת�����ο���ѹѡ��λ
			00���ⲿ VREF ����
			01���ڲ� A/D ת������Դ VDD
			1x���ⲿ VREF ����
			�⼸λ����ѡ�� A/D ת�����ο���ѹ���� SAVRS λ�α�����Ϊ��01����ѡ��
			�ڲ� A/D ת������Դ��Ϊ�ο���ѹԴʱ����ע�⡣�����������ʱ��Ӧ���?
			���� TMPC �Ĵ����е� VREFS ����λ�Ա��� VREF ���ű�����Ϊ�ο���ѹ��
			�롣����VREF �����ϵ��ⲿ�����ѹ���������ڲ�?A/D ת������Դ���⽫
			�����޷�Ԥ�ڵĽ����?
		Bit 2~0 SACKS2~SACKS0��A/D ת����ʱ��Դѡ��λ
		000��fSYS
		001��fSYS/2
		010��fSYS/4
		011��fSYS/8
		100��fSYS/16
		101��fSYS/32
		110��fSYS/64
		111��fSYS/128
	*/
	_ptmc0 = 0b00000000;	//16M/4=4M
	/*
		Bit 7 PTPAU��PTM ��������ͣ����λ
			0������
			1����ͣ
		Bit 6~4 PTCK2~PTCK0��ѡ�� PTM ����ʱ��λ
			000��fSYS/4
			001��fSYS
			010��fH/16
			011��fH/64
			100��fSUB
			101��fSUB
			110��PTCK ������
			111��PTCK �½���
		Bit 3 PTON��PTM ������ On/Off ����λ
			0��Off
			1��On
		Bit 2~0 δ���壬��Ϊ��0_ton=1;
	*/
	_ptmc1 = 0b11000001;	//Timer mode, ccra clr
	
	//_ptmal = 250;			//250*0.5=125uS
	_ptmal = (500-256);	
	_ptmah = 1;	
	
	_ptmrpl = 0;			
	_ptmrph = 0;
			
	_ptmaf = 0;
	_mf2f = 1;
	_ptmae = 1;
	_mf2e = 1;
	_pton = 1;
	
	_emi = 1;	
}


void 	Work_SensorAdcRegInit(void)
{
	
	gu8v_BatLowCnt = 0;
	gu8v_BatNormalCnt = 0;
	
	gubv_AdcChannelSelect = 0;
	
	gu8v_AdSampCnt1 = 0;
	gu16v_AdcValue1 = 0;
	gu16v_AdMaxTemp1 = 0x0000;
	gu16v_AdMinTemp1 = 0xffff;
	
	gu8v_AdSampCnt2 = 0;
	gu16v_AdcValue2 = 0;
	gu16v_AdMaxTemp2 = 0x0000;
	gu16v_AdMinTemp2 = 0xffff;
	
	gu8v_AbPressureNoFullAdcCnt = 0;
	gu8v_AbPressureFullAdcCnt = 0;	
}


void 	Init_TimerReg(void)
{
	TimeFlag1.byte = 0x00;
	TimeFlag2.byte = 0x00;
	gu8v_Delay1mS = 0x00;
	gu8v_Delay1mS = 0x00;
	gu8v_Delay5mS = 0x00;
	gu8v_Delay50mS = 0x00;
	gu8v_Delay100mS = 0x00;
	gu8v_Delay500mS = 0x00;
	gu8v_Delay1S = 0x00;
}
void 	Work_StatusRegInit(void)
{
	DcfFlag1.byte = 0x00;
	WorkModeFlag.byte = 0x00;
	gu8v_ButtonOnTkDelay = 200;
	//gu16v_JiaoTiTime = C_15_M;
	//gu8v_JiaoTiMode = 0;
	gu8v_AcOffDebounce = 20;
	gu8v_PressureMode = 4;
	gu8v_LowVoltage = 0;
	gubv_PowerStatus = 0;
	gu16v_AutoModeCycle = 0;
	gubv_AbPressureFirstFull = 0;
	gubv_LockStatus = 0;
	gu8v_LockDelay60S = C_60S;
	gubv_VoliceOn = 1;
	gubv_AbPressureFull = 0;
	gubv_StaticMode = 1;
	gu8v_PreKeyDownDisTime = 0;
	
	gu16v_AbPressureLowErrTimeCmp = C_90_M;
	gu16v_AbPressureLowErrTimeCnt = 0;
	gubv_AbSensorFangQiEn = 0;
	gubv_AbSensorErrAlarmMode = 0;
	
	gu16v_FunPressureLowErrTimeCmp = C_90_M;
	gu16v_FunPressureLowErrTimeCnt = 0;
	gubv_FunSensorFangQiEn = 0;
	gubv_FunSensorErrAlarmMode = 0;

	gu8v_AbNumDisValue = 0;
	gu8v_AbNumDisCurrentValue = 0;
	gu16v_AbNumDisValueOld = 0;
	
	gubv_AbMotoOff = 0;
	gubv_FunMotoOff = 0;
	
}
////===============================================================
//// Usegu8v_Init
////===============================================================
void User_Init(void)
{
	Work_StatusRegInit();
	Work_SensorAdcRegInit();
	Init_TimerReg();
	gu8v_WorkMode = C_POWER_ON_MODE;
	gu8v_PowerOnDelay = 15;
	gubv_PowerOnReadEe = 1;
	gubv_FactoryTestMode = 0;
	gubv_CalMode = 0;
	gu8v_CalModeIndex = 0;
	gu8v_RfIdCopyTime = 100;
	DcfFlag1.byte = 0x03;//AB DCF ON

	drv_tm1652_init();
}

