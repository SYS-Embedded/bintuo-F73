
#ifndef __VARIANTS_H__
#define __VARIANTS_H__


#include	"MyDefine.h"

extern	 	volatile		unsigned char  	gu8v_Delay1mS;
extern	 	volatile		unsigned char  	gu8v_Delay5mS;
extern	 	volatile		unsigned char  	gu8v_Delay10mS;
extern	 	volatile 		unsigned char  	gu8v_Delay50mS;
extern	 	volatile		unsigned char  	gu8v_Delay100mS;
extern	 	volatile		unsigned char  	gu8v_Delay500mS;
extern	 	volatile		unsigned char  	gu8v_Delay1S;

extern 	  	volatile		unsigned char  	gu8v_BeepStep;
extern 	    volatile		unsigned char  	gu8v_BeepTime;
extern 	  	volatile		unsigned char  	gu8v_TimerMode;
extern 	    volatile		unsigned char  	gu8v_BeepType;
extern 	  	volatile		unsigned char  	gu8v_BeepCnt;

extern 	   	volatile		unsigned char  	gu8v_WorkMode;
extern 	   	volatile		unsigned char  	gu8v_AbPwmDuty;
extern 	  	volatile		unsigned char  	gu8v_AbPwmDelay;
extern 	   	volatile		unsigned char  	gu8v_FunPwmDuty;
extern 	  	volatile		unsigned char  	gu8v_FunPwmDelay;

extern 	  	volatile		unsigned char  	gu8v_AbPwmOutPinDuty;
extern 	  	volatile		unsigned char  	gu8v_AbPwmOutPinDelay;
extern 	  	volatile		unsigned char  	gu8v_FunPwmOutPinDuty;
extern 	  	volatile		unsigned char  	gu8v_FunPwmOutPinDelay;

extern 	   	volatile		unsigned char  	gu8v_PressureMode;
extern 	  	volatile		unsigned char  	gu8v_JiaoTiMode;
extern	   	volatile		unsigned char	gu8v_DisplayBuf[14];

extern	 	volatile		unsigned char 	gu8v_KeyDebounce;
extern	 	volatile		unsigned char 	gu8v_KeyOffDebounce;
extern	 	volatile		unsigned char  	gu8v_KeyLongDelay;
extern	 	volatile		unsigned int  	gu16v_KeyBuffer;
extern	 	volatile		unsigned int  	gu16v_KeyValue;
extern	 	volatile		unsigned int  	gu16v_JiaoTiTime;
extern	 	volatile		unsigned int  	gu16v_JiaoTiTimeCnt;
extern	 	volatile		unsigned int  	gu16v_JiaoTiTimeCmp;
extern	 	volatile		unsigned char  	gu8v_12vInDebounce;
extern	 	volatile		unsigned char  	gu8v_12vOutDebounce;
extern	 	volatile		unsigned char  	gu8v_AcOffDebounce;

extern	 	volatile		unsigned char  	gu8v_IrRecData[4];
extern	 	volatile		unsigned char  	gu8v_IrDelay;
extern	 	volatile		unsigned char  	gu8v_IrBitCnt;
extern	 	volatile		unsigned char  	gu8v_IrSampling;
extern	 	volatile		unsigned char  	gu8v_IrSampStep;
extern	 	volatile		unsigned int	gu16v_AbSensroCalCopy;
extern	 	volatile		unsigned char	gu8v_CalModeIndex;
extern	 	volatile		unsigned int  	gu16v_AutoModeCycle;

extern	 	volatile  		unsigned char 	gu8v_AdSampCnt1;
extern	 	volatile  		unsigned int 	gu16v_AdMaxTemp1;
extern	 	volatile  		unsigned int 	gu16v_AdMinTemp1;
extern	 	volatile  		unsigned int 	gu16v_AdcValue1;

extern	 	volatile  		unsigned char 	gu8v_AdSampCnt2;
extern	 	volatile  		unsigned int 	gu16v_AdMaxTemp2;
extern	 	volatile  		unsigned int 	gu16v_AdMinTemp2;
extern	 	volatile  		unsigned int 	gu16v_AdcValue2;
extern	 	volatile  		unsigned int 	gu16v_ABAdcSensor;
extern	 	volatile  		unsigned int 	gu16v_FunAdcSensor;
extern	 	volatile		unsigned int 	gu16v_CalData;
extern	 	volatile		unsigned int	gu16v_Ab7P5mmHgData;
extern	 	volatile		unsigned int	gu16v_Ab150CalDataEe;
extern	 	volatile		unsigned int	gu16v_Ab150CalDataEeCopy;
extern	 	volatile		unsigned int	gu16v_AbAdcZeroData;
extern	 	volatile		unsigned int	gu16v_AbAdcZeroDataSum;
extern	 	volatile		unsigned int	gu16v_AbSensroCalCopy;
extern	 	volatile		unsigned int	gu16v_AbSensroCmp;
extern	 	volatile		unsigned char	gu8v_AbPressureNoFullCmp;
extern	 	volatile		unsigned char	gu8v_AbPressureNoFullAdcCnt;
extern	 	volatile		unsigned char	gu8v_AbPressureFullAdcCnt;
extern	 	volatile		unsigned char	gu8v_AbPressureLowNorAdcCnt;

extern	 	volatile		unsigned int	gu16v_Fun7P5mmHgData;
extern	 	volatile		unsigned int	gu16v_Fun150CalDataEe;
extern	 	volatile		unsigned int	gu16v_Fun150CalDataEeCopy;
extern	 	volatile		unsigned int	gu16v_FunAdcZeroData;
extern	 	volatile		unsigned int	gu16v_FunAdcZeroDataSum;
extern	 	volatile		unsigned int	gu16v_FunSensroCalCopy;
extern	 	volatile		unsigned int	gu16v_FunSensroCmp;
extern	 	volatile		unsigned char	gu8v_FunPressureNoFullCmp;
extern	 	volatile		unsigned char	gu8v_FunPressureLowAdcCnt;
extern	 	volatile		unsigned char	gu8v_FunPressureFullAdcCnt;

extern	 	volatile		unsigned char	gu8v_AbGetAdcZeroCnt;

extern	 	volatile		unsigned int	gu16v_EeTemp;

extern	 	volatile		unsigned char  	gu8v_BatLowCnt;
extern	 	volatile		unsigned char  	gu8v_BatNormalCnt;
extern	 	volatile		unsigned char	gu8v_FactoryDebounce;
extern	 	volatile		unsigned char	gu8v_CalDcfScan;
extern	 	volatile		unsigned char	gu8v_UartDelayClearRxIndex;
extern	 	volatile		unsigned char	gu8v_UartRxLength;
extern	 	volatile		unsigned char	gu8v_UartTxIndex;
extern	 	volatile		unsigned char	gu8v_UartTxLength;
extern	 	volatile		unsigned char	gu8v_UartTxBuf[20];
extern	 	volatile		unsigned char	gu8v_UartRxBuf[20];
extern	 	volatile		unsigned char	gu8v_ButtonOnTkDelay;
extern	 	volatile		unsigned char	gu8v_LvdDebounce;
extern	 	volatile		unsigned char	gu8v_PowerOnDelay;
extern	 	volatile		unsigned char	gu8v_RfIdCopyTime;
extern	 	volatile		unsigned char	gu8v_RfIdCopyKeyCnt;
extern	 	volatile		unsigned char	gu8v_RfIdCopyLedDisStep;
extern	 	volatile		unsigned char	gu8v_433RecData[6];
extern	 	volatile		unsigned char	gu8v_433RecValue[6];
extern	 	volatile		unsigned char	gu8v_433CopyIdData1[4];
extern	 	volatile		unsigned char	gu8v_433_H_cnt;
extern	 	volatile		unsigned char 	gu8v_433_L_Cnt;
extern	 	volatile		unsigned char 	gu8v_433BitCnt;
extern	 	volatile		unsigned char 	gu8v_433ByteCnt;
extern	 	volatile		unsigned char 	gu8v_VoicePluse;
extern	 	volatile		unsigned char 	gu8v_KeyBuf1;
extern	 	volatile		unsigned char 	gu8v_KeyBuf2;
extern	 	volatile		unsigned char 	gu8v_KeyBuf3;
extern	 	volatile		unsigned char 	gu8v_LockDelay60S;
extern	 	volatile		unsigned char 	gu8v_PreKeyDownDisTime;

extern volatile 		unsigned 	char 	gu8v_RfSendStep;
extern volatile 		unsigned 	char 	gu8v_RfSendCycle;
extern volatile 		unsigned 	char 	gu8v_RfBitCycle;
extern volatile 		unsigned 	char 	gu8v_RfBitDuty;
extern volatile 		unsigned 	char 	gu8v_RfSendByteCnt;
extern volatile 		unsigned 	char 	gu8v_RfSendBitCnt;

extern volatile 		unsigned 	char 	gu8v_AbNumDisValue;
extern volatile 		unsigned 	char 	gu8v_AbNumDisCurrentValue;
extern volatile 		unsigned 	int 	gu16v_AbNumDisValueOld;
extern volatile 		unsigned 	char 	gu8v_FunNumDisValue;
extern volatile 		unsigned 	char 	gu8v_NumDisTemp;
extern volatile 		unsigned 	char 	gu8v_PressureModeCopy;
extern volatile			unsigned 	int		gu16v_AbPressureLowErrTimeCmp;
extern volatile			unsigned 	int		gu16v_AbPressureLowErrTimeCnt;
extern volatile			unsigned 	int		gu16v_FunPressureLowErrTimeCmp;
extern volatile			unsigned 	int		gu16v_FunPressureLowErrTimeCnt;

extern volatile 		unsigned 	char 	gu8v_AbSensorPressureCnt;
extern volatile 		unsigned 	char 	gu8v_FunSensorPressureCnt;
extern volatile 		unsigned 	char 	gu8v_AbFangQiTime;
extern volatile 		unsigned 	char 	gu8v_AbSensorDisCnt;

extern volatile 		unsigned 	char 	gu8v_AbSensorLowPwmCnt;
extern volatile 		unsigned 	char 	gu8v_AbSensorHighPwmCnt;
extern volatile 		unsigned 	char 	gu8v_FunSensorLowPwmCnt;
extern volatile 		unsigned 	char 	gu8v_FunSensorHighPwmCnt;
extern volatile 		unsigned 	char 	gu8v_12KpDebounce;
extern volatile 		unsigned 	char 	gu8v_7KpDebounce;

extern volatile 		unsigned 	char 	gu8v_FunMotoOffDebounce;
extern volatile 		unsigned 	char 	gu8v_AbMotoOffDebounce;
extern volatile 		unsigned 	char 	gu8v_FunMotoOnDebounce;
extern volatile 		unsigned 	char 	gu8v_AbMotoOnDebounce;
//extern	 	volatile		unsigned char 	gu8v_IdLowByte;
//extern	 	volatile		unsigned char 	gu8v_IdHighByte;

extern	 	volatile 		__flag_type			KeyFlag1;
#define			gubv_KeyShortAL					KeyFlag1.bits.b0
#define			gubv_KeyShortSleep				KeyFlag1.bits.b1
#define			gubv_KeyShortAutoRL				KeyFlag1.bits.b2
#define			gubv_KeyShortRight				KeyFlag1.bits.b3
#define			gubv_KeyShortLeft				KeyFlag1.bits.b4
#define			gubv_KeyShortTaiTui				KeyFlag1.bits.b5
#define			gubv_KeyShortQiBei				KeyFlag1.bits.b6

extern	 	volatile 		__flag_type			KeyFlag2;
#define			gubv_KeyShort10M				KeyFlag2.bits.b0
#define			gubv_KeyShort15M				KeyFlag2.bits.b1
#define			gubv_KeyShort20M				KeyFlag2.bits.b2
#define			gubv_KeyShortNorPre				KeyFlag2.bits.b3
#define			gubv_KeyShortLowPre				KeyFlag2.bits.b4
#define			gubv_KeyShortAlermOff			KeyFlag2.bits.b5
#define			gubv_KeyShortPreDec				KeyFlag2.bits.b6
#define			gubv_KeyShortPreAdd				KeyFlag2.bits.b7

extern	 	volatile 		__flag_type			KeyFlag3;
#define			gubv_KeyShortLock				KeyFlag3.bits.b0
#define			gubv_KeyShortPower				KeyFlag3.bits.b1
#define			gubv_KeyShortVoliceOff			KeyFlag3.bits.b2


extern    volatile		__flag_type						TimeFlag1;
#define			gubv_10mS								TimeFlag1.bits.b0
#define			gubv_5mS								TimeFlag1.bits.b1
#define			gubv_50mS								TimeFlag1.bits.b2
#define			gubv_100mS								TimeFlag1.bits.b3
#define			gubv_500mS								TimeFlag1.bits.b4
#define			gubv_1S									TimeFlag1.bits.b5
#define			gubv_500mS_Flash						TimeFlag1.bits.b6
#define			gubv_1S_1								TimeFlag1.bits.b7

extern    volatile		__flag_type						TimeFlag2;
#define			gubv_1S_2								TimeFlag2.bits.b0
#define			gubv_1S_3								TimeFlag2.bits.b1

extern    volatile		__flag_type						WorkFlag1;
#define			gubv_BeepOn								WorkFlag1.bits.b0
#define			gubv_ZeroStatus							WorkFlag1.bits.b1
#define			gubv_ZeroStatusCopy						WorkFlag1.bits.b2
#define			gubv_AbPressureFirstFull				WorkFlag1.bits.b3
#define			gubv_KeyPressed							WorkFlag1.bits.b4
#define			gubv_KeyLongPressed						WorkFlag1.bits.b5
#define			gubv_AcVoltageOFF						WorkFlag1.bits.b6
#define			gubv_Dc12vOFF							WorkFlag1.bits.b7

extern    volatile		__flag_type						WorkFlag2;
#define			gubv_JiaoTiA							WorkFlag2.bits.b0
#define			gubv_IrRecUpdata						WorkFlag2.bits.b1
#define			gubv_AutoLeftFanShenMode				WorkFlag2.bits.b2
#define			gubv_AutoRightFanShenMode				WorkFlag2.bits.b3
#define			gubv_12vOff								WorkFlag2.bits.b4
#define			gubv_PowerButtonOff						WorkFlag2.bits.b5
#define			gubv_AbMotoOff	 						WorkFlag2.bits.b6
#define			gubv_FunMotoOff							WorkFlag2.bits.b7

extern    volatile		__flag_type						WorkFlag3;
#define			gubv_500mS_1							WorkFlag3.bits.b0
#define			gu8v_UartRecOnePacket					WorkFlag3.bits.b1
#define			gu8v_LowVoltage							WorkFlag3.bits.b2
#define			gu8v_Rf433RecOk							WorkFlag3.bits.b3
#define			gu8v_Rf433ReadCopy						WorkFlag3.bits.b4
#define			gubv_PowerStatus						WorkFlag3.bits.b5
#define			gubv_WriteRfIdEe						WorkFlag3.bits.b6
#define			gubv_Pin433Read							WorkFlag3.bits.b7

extern    volatile		__flag_type						WorkFlag4;
#define			gubv_SensorAdUpdata						WorkFlag4.bits.b0
#define			gubv_GetZeroData						WorkFlag4.bits.b1
#define			gubv_ZeroUpdataEe1						WorkFlag4.bits.b2
#define			gubv_CalMode							WorkFlag4.bits.b3
#define			gubv_StartStatus						WorkFlag4.bits.b4
#define			gubv_AbPressureFull						WorkFlag4.bits.b5
#define			gubv_WriteCalEe							WorkFlag4.bits.b6
#define			gubv_PowerOnReadEe						WorkFlag4.bits.b7

extern    volatile		__flag_type						WorkFlag5;
#define			gubv_AbSensorFangQiEn					WorkFlag5.bits.b0
#define			gubv_FactoryTestMode					WorkFlag5.bits.b1
#define			gubv_StaticMode							WorkFlag5.bits.b2
#define			gubv_LockStatus							WorkFlag5.bits.b3
#define			gubv_VoliceOn							WorkFlag5.bits.b4
#define			gubv_AdcChannelSelect					WorkFlag5.bits.b5
#define			gubv_FunPressureFull					WorkFlag5.bits.b6
#define			gubv_FunGetZeroData						WorkFlag5.bits.b7

extern    volatile		__flag_type						WorkFlag6;
#define			gubv_FunPressureFirstFull				WorkFlag6.bits.b0
#define			gubv_StaticModeCopy						WorkFlag6.bits.b1
#define			gubv_AbSensorErrAlarmMode				WorkFlag6.bits.b2
#define			gubv_FunSensorErrAlarmMode				WorkFlag6.bits.b3
#define			gubv_FunSensorFangQiEn					WorkFlag6.bits.b4

extern    volatile		__flag_type						WorkModeFlag;	
#define			gubv_AutoMode							WorkModeFlag.bits.b0
#define			gubv_QiBeiMode							WorkModeFlag.bits.b1
#define			gubv_DcfLeftFanShenMode					WorkModeFlag.bits.b2
#define			gubv_DcfRightFanShenMode				WorkModeFlag.bits.b3
#define			gubv_TaituiMode							WorkModeFlag.bits.b4

extern    volatile		__flag_type						DcfFlag1;
#define			gubv_DcfA								DcfFlag1.bits.b0
#define			gubv_DcfB								DcfFlag1.bits.b1
#define			gubv_DcfQiBei							DcfFlag1.bits.b2
#define			gubv_DcfRightFanShen					DcfFlag1.bits.b3
#define			gubv_DcfLeftFanShen						DcfFlag1.bits.b4
#define			gubv_DcfTaiTui							DcfFlag1.bits.b5

extern   volatile 		__u16byte_type		gu16v_IdData;

#endif 