
#include "Initial.h"

/**************************************************
**************************************************/
/**************************************************
*函数名称：void  Sys_Init(void) 
*函数功能：系统初始化
*入口参数：void
*出口参数：void  
**************************************************/
void  Sys_Init(void)
{	
	_pf =   0b00100000;
	_pfc =  0b00100000;
	_pfpu = 0b00100000;
	
	_pe =   0b00000000;
	_pec =  0b00000000;
	_pepu = 0b00000000;
	
	_pac =  0b00001001;
	_pa =   0b00001001;
	_papu = 0b00001001;

	_pbc =  0b00001111;
	_pb =   0b00001111;
	_pbpu = 0b00001100;
	
	_pc =   0b00000000;
	_pcc =  0b00000000;
	_pcpu = 0b00000000;
	
	_pd =   0b00000000;
	_pdc =  0b00000000;
	_pdpu = 0b00000000;
	
	//_lvrc=0b00110011;//：2.55V
	_lvrc=0b01010101;//：2.1V
	/*
		Bit 7~0 LVS7~LVS0： LVR 电压选择
			01010101： 2.1V
			00110011： 2.55V
			10011001： 3.15V
			10101010： 3.8V
	*/
	_lvdc=0b00011001;//：2.2V
	/*
		Bit 7~6 未定义，读为“0”
		Bit 5 LVDO：LVD 输出标志位
			0：未检测到低电压
			1：检测到低电压
		Bit 4 LVDEN：低电压检测控制位
			0：除能
			1：使能
		Bit 3 VBGEN：Bandgap 电压输出控制位
			0：除能
			1：使能
		注意，当 LVD 或 LVR 使能或当 VBGEN 置位时，Bandgap 会自动使能。
			Bit 2~0 VLVD2~VLVD0：选择 LVD 电压位
			000：2.0V
			001：2.2V
			010：2.4V
			011：2.7V
			100：3.0V
			101：3.3V
			110：3.6V
			111：4.0V
	*/
	_wdtc=0b01010111;
	/*
		Bit 7~3 WE4~WE0： WDT 功能控制
		01010 或 10101：使能
		其它值：单片机复位
		如果由于不利的环境因素使这些位变为其它值，单片机将复位。复位动作发生
		在 tSRESET 延迟时间后，且 CTRL 寄存器的 WRF 位将置为“ 1”。
		Bit 2~0 WS2~WS0： WDT 溢出周期选择位
		000： 28/fSUB
		001： 210/fSUB
		010： 212/fSUB
		011： 214/fSUB
		100： 215/fSUB
		101： 216/fSUB
		110： 217/fSUB
		111： 218/fSUB
	*/
	_ifs0=0b00000000;
	/*
		Bit 7~6 未定义，读为“0”
		Bit 5~4 IFS05~IFS04：SCS 输入源引脚选择
			00：PA2
			01：PA3
			10：PA2
			11：PA3
		Bit 3~2 IFS03~IFS02：PTPI 输入源引脚选择
			00：PB2
			01：PB4
			10：PB2
			11：PB4
		Bit 1~0 IFS01~IFS00：STPI 输入源引脚选择
			00：PE2
			01：PE3
			10：PE2
			11：PE3
	*/
	_ifs1=0b00000000;
	/*
		Bit 7~6 未定义，读为“0”
		Bit 5~4 IFS15~ IFS14：SDI/SDA 输入源引脚选择
			00：PB0
			01：PA5
			10：PB0
			11：PA5
		Bit 3~2 IFS13~ IFS12：SCK/SCL 输入源引脚选择
			00：PB1
			01：PB1
			10：PA1
			11：PA1
		Bit 1~0 IFS11~ IFS10：RX 输入源引脚选择
			00：PB3
			01：PB3
			10：PA1
			11：PA1
	*/
	_pas0=0b00000000;
	_pas1=0b00000000;
	_pbs0=0b00001111;//AN1,AN0
	/*
		Bit 7~6 PBS07~PBS06：PB3 引脚共用功能选择
			00：PB3
			01：RX
			10：PB3
			11：AN3
		Bit 5~4 PBS05~PBS04：PB2 引脚共用功能选择
			00：PB2/PTPI
			01：TX
			10：PTP
			11：AN2
		Bit 3~2 PBS03~PBS02：PB1 引脚共用功能选择
			00：PB1
			01：SCK/SCL
			10：PB1
			11：AN1
		Bit 1~0 PBS01~PBS00：PB0 引脚共用功能选择
			00：PB0
			01：SDI/SDA
			10：VREF
			11：AN0
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
		Bit 7 PANS7：PA7 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 6 PANS6：PA6 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 5 PANS5：PA5 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 4~2 未定义，读为“0”
		Bit 1 PANS1：PA1 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 0 未定义，读为“0
	*/
	_pens=0b00000000;
	/*
		Bit 7 PENS7：PE7 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 6 PENS6：PE6 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 5~0 未定义，读为“0”
	*/
	_pfns=0b00000000;
	/*
		Bit 7~6 未定义，读为“0”
		Bit 5 PFNS5：PF5 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 4 PFNS4：PF4 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 3 PFNS3：PF3 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 2 PFNS2：PF2 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 1 PFNS1：PF1 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
		Bit 0 PFNS0：PF0 灌电流选择位 ( NMOS 调节 )
			0：Level 0 ( 最小 )
			1：Level 1 ( 最大 )
	*/
	_sadc0 = C_ADC_CH_AB;
	/*
	Bit 7 START：启动 A/D 转换位
		0→1→0：启动 A/D 转换
		此位用于初始化 A/D 转换过程。通常此位为低，但如果设为高再被清零，将初
		始化 A/D 转换过程。
	Bit 6 ADBZ：A/D 转换忙碌标志位
		0：A/D 转换结束或未开始转换
		1：A/D 转换中
		此位用于表明 A/D 转换过程是否完成。当 START 位由低变为高再变为低时，
		ADBZ 位为高，表明 A/D 转换已初始化。A/D 转换结束后，此位被清零。
	Bit 5 ADCEN：A/D 转换器使能 / 除能控制位
		0：除能
		1：使能
		此位控制 A/D 内部功能。该位被置高将使能 A/D 转换器。如果该位设为低
		将关闭 A/D 转换器以降低功耗。当 A/D 转换器功能除能时，A/D 数据寄存器
		SADOH 和 SADOL 的内容将被不变。
	Bit 4 ADRFS：A/D 转换数据格式选择位
		0：A/D 转换数据格式 → SADOH=D[11:4]; SADOL=D[3:0]
		1：A/D 转换数据格式 → SADOH=D[11:8]; SADOL=D[7:0]
		此位控制存放在两个 A/D 数据寄存器中的 12 位 A/D 转换结果的格式。细节方
		面请参考 A/D 转换器数据寄存器章节。
	Bit 3~0 SACS3~SACS0：A/D 转换器外部输入通道选择位
		0000：AN0
		0001：AN1
		0010：AN2
		0011：AN3
		0100：AN4
		0101：AN5
		0110：AN6
		0111：AN7
		1xxx：无通道，输入浮空
	*/
	_sadc1=0b00001011; //vdd,fsys/8
	/*
		Bit 7~5 SAINS2~SAINS0：A/D 转换器输入信号选择位
			000：外部来源 – 外部模拟通道输入 ANn
			001：内部来源 – 内部 Bandgap 参考电压 VBG
			010~100：内部来源 – 保留，接地
			101~111：外部来源 – 外部模拟通道输入 ANn
			若 SAINS 位段设置为“001”以选择内部模拟信号进行转换时必须特别小心。
			当选择转换内部模拟信号，SACS 位段必须设置为“1xxx”。否则外部通道输入
			将与内部模拟信号连接，将导致不可预期的后果。
		Bit 4~3 SAVRS1~SAVRS0：A/D 转换器参考电压选择位
			00：外部 VREF 引脚
			01：内部 A/D 转换器电源 VDD
			1x：外部 VREF 引脚
			这几位用于选择 A/D 转换器参考电压。若 SAVRS 位段被设置为“01”以选择
			内部 A/D 转换器电源作为参考电压源时需多加注意。当此情况发生时，应正确
			配置 TMPC 寄存器中的 VREFS 控制位以避免 VREF 引脚被配置为参考电压输
			入。否则，VREF 引脚上的外部输入电压将连接至内部 A/D 转换器电源，这将
			导致无法预期的结果。
		Bit 2~0 SACKS2~SACKS0：A/D 转换器时钟源选择位
		000：fSYS
		001：fSYS/2
		010：fSYS/4
		011：fSYS/8
		100：fSYS/16
		101：fSYS/32
		110：fSYS/64
		111：fSYS/128
	*/
	_ptmc0 = 0b00000000;	//16M/4=4M
	/*
		Bit 7 PTPAU：PTM 计数器暂停控制位
			0：运行
			1：暂停
		Bit 6~4 PTCK2~PTCK0：选择 PTM 计数时钟位
			000：fSYS/4
			001：fSYS
			010：fH/16
			011：fH/64
			100：fSUB
			101：fSUB
			110：PTCK 上升沿
			111：PTCK 下降沿
		Bit 3 PTON：PTM 计数器 On/Off 控制位
			0：Off
			1：On
		Bit 2~0 未定义，读为“0_ton=1;
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
	gu8v_PressureMode = 0x09;
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
}

