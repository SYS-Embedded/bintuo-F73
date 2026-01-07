
#ifndef 			_MYDEFINE_H_
#define 			_MYDEFINE_H_

#include 	<BS66F360C.h>
//================== macro define ================

typedef struct {
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} __flag_bits;

typedef union {
	__flag_bits bits;
	__sfr_byte	byte;
} __flag_type;

typedef struct {
	unsigned char byte1 ;
	unsigned char byte2 ;
	unsigned char byte3 ;
	unsigned char byte4 ;
} __u32_bytes;

typedef union {
	__u32_bytes 	byte;
	unsigned long	u32byteS;
} __u32byte_type;

typedef struct {
	unsigned char byte1 ;
	unsigned char byte2 ;
} __u16_bytes;
typedef union {
	__u16_bytes 	byte;
	unsigned int	u16byteS;
} __u16byte_type;



#define 			uchar 							unsigned char
#define 			uint 							unsigned int

#define 			C_DEBUG_MODE		 		0			//0:normal mode,1:debug mode

#define				P_FACTORY_TEST				_pa0
#define				P_TEST						_pa2


#define 			C_POWER_ON_MODE		 		1
#define 			C_WORK_OFF_MODE		 		2
#define 			C_WORK_ON_MODE		 		3

//#define				C_ADC_BAT_LOW						1365	//3.2V bat,3.2/4/2.4*4095=1365
//#define				C_ADC_BAT_NORMAL				1450	//3.4V bat,3.4/4/2.4*4095=1450

//#define				C_ADC_BAT_LOW						1536	//3.6V bat,3.6/4/2.4*4095=1536
//#define				C_ADC_BAT_NORMAL				1621	//3.8V bat,3.8/4/2.4*4095=1621

#define				C_ADC_BAT_LOW						1792	//4.2V bat,4.2/4/2.4*4095=1792
//#define				C_ADC_BAT_NORMAL				1877	//4.4V bat,4.4/4/2.4*4095=1877
#define				C_ADC_BAT_NORMAL					1919	//4.5V bat,4.5V/4/2.4*4095=1919

/************************ TEST PIN  *****************************/		
/************************ TEST PIN  *****************************/
/************************ BEEP ************************************/

#define				P_BEEP										_pa3			//BEEP SOUND

#define				C_BP_WORK_ON								1
#define				C_BP_WORK_OFF								2
#define				C_BP_NORMAL									3
#define				C_BP_ALARM									4
#define				C_WIFI_FACTORY_TEST_ERROR					5
#define				C_BP_ION_OFF								6
#define				C_BP_ERROR									7

#define				C_BP_ON										1
#define				C_BP_OFF									0

/************************ BEEP ************************************/
/************************ IR  ************************************/

#define				P_IR					_pb2
#define				C_IR_USERID_LOW			0x4c
#define				C_IR_USERID_HIGHT		0xa0
#define 			C_IR_DELAY	 			3			

#define 			C_IR_KEY_POWER						0x80
#define 			C_IR_KEY_ZUO_ZI	 					0xc0
#define 			C_IR_KEY_AUTO						0x20
#define 			C_IR_KEY_LEFI_FANSHEN	 			0xa0
#define 			C_IR_KEY_RIGHT_FANSHEN				0x60
#define 			C_IR_KEY_QIBEI	 					0xe0
#define 			C_IR_KEY_TAITUI						0x10
#define 			C_IR_KEY_LOCK		 				0x90
#define 			C_IR_KEY_VOICE		 				0x50

#define				C_RF433_BIT_TIME1_MIN				1
#define				C_RF433_BIT_TIME1_MAX				5//3.2
#define				C_RF433_BIT_TIME2_MIN				5
#define				C_RF433_BIT_TIME2_MAX				12//9.6
#define				C_RF433_BIT_TIME3_MIN				30
#define				C_RF433_BIT_TIME3_MAX				50	//96

/************************ KEY ************************************/

//#define				C_KEYVALUE_PRE_DEC				0x0001 
//#define				C_KEYVALUE_PRE_ADD				0x0002 
//#define				C_KEYVALUE_ALERM_OFF			0x0004 
//#define				C_KEYVALUE_STATIC				0x0008
//#define				C_KEYVALUE_AUTO					0x0010
//#define				C_KEYVALUE_QiBei				0x0020
//#define				C_KEYVALUE_LEFT					0x0040
//#define				C_KEYVALUE_RIGHT				0x0080
//#define				C_KEYVALUE_TAITUI				0x0100
//#define				C_KEYVALUE_JIAOTI				0x0200
//#define				C_KEYVALUE_POWER				0x0400

#define				C_KEYVALUE_AL					0x01
#define				C_KEYVALUE_SLEEP				0x02
#define				C_KEYVALUE_VOLICE_OFF			0x20

#define				C_KEYVALUE_AUTO_RL				0x40
#define				C_KEYVALUE_RIGHT				0x08
#define				C_KEYVALUE_LEFT					0x80
#define				C_KEYVALUE_TAITUI				0x40
#define				C_KEYVALUE_QiBei				0x08

#define				C_KEYVALUE_10M					0x04
#define				C_KEYVALUE_15M					0x02
#define				C_KEYVALUE_20M					0x01
#define				C_KEYVALUE_NORMAL_PRE			0x01
#define				C_KEYVALUE_LOW_PRE				0x02
#define				C_KEYVALUE_ALARM				0x04

#define				C_KEYVALUE_LOCK					0x08
#define				C_KEYVALUE_PRE_DEC				0x20
#define				C_KEYVALUE_PRE_ADD				0x10 
#define				C_KEYVALUE_POWER				0x80
/************************ KEY ************************************/
/************************ IO ************************************/
#define	        	P_AB_MOTO     					_pe4
#define	        	P_FUN_MOTO     					_pe5
#define	        	P_DC_MOTO     					_pa5
#define				C_MOTO_ON						1
#define				C_MOTO_OFF						0

#define				C_DUTY_100P_L					0
#define				C_DUTY_100P_H					40

#define				C_DUTY_60P_L					5
#define				C_DUTY_60P_H					30

#define	        	P_DCF_B    						_pf2
#define	        	P_DCF_A    						_pf1

#define	        	P_DCF_QiBei    					_pe6  
#define	        	P_DCF_RightFanShen   			_pf0
#define	        	P_DCF_LeftFanShen    			_pe7 
#define	        	P_DCF_TaiTui    				_pe2

#define			 	C_DCF_OFF					 	 0
#define				C_DCF_ON					  	 1

#define			 	C_AB_DCF_OFF					 1// 
#define				C_AB_DCF_ON					  	 0// 

//#define	        	P_12V_IN    					_pa7
#define	        	P_ZERO    						_pb3
#define	        	P_KEY_POWER    					_pf5

#define	        	P_Voice   						_pa7
#define				C_DATA_HIGH						1
#define				C_DATA_LOW						0
#define				C_RF_SEND_START					0X01
#define				C_RF_SEND_DATA					0X02
#define				C_RF_SEND_STOP					0X03
#define				C_RF_SEND_NULL					0X00
#define				C_IR_USERID						0x55
#define				C_BIT_CYCLE					8
#define				C_BIT_SHORT_DUTY			(C_BIT_CYCLE-2)				
#define				C_BIT_LONG_DUTY				(C_BIT_CYCLE-6)		
#define				C_SEND_FIRST_BIT			0X01	//先发低位
#define				C_SEND_START_CYCLE			40

#define				C_ADC_CH_AB					0b00110000
#define				C_ADC_CH_FUN				0b00110001

#define				C_VOICE_WAIT_FUN_ON			1
#define				C_VOICE_POWER_ON			2
#define				C_VOICE_POWER_OFF			3
#define				C_VOICE_AL					4
#define				C_VOICE_SLEEP				5
#define				C_VOICE_QB_ON				6
#define				C_VOICE_QB_OFF				7
#define				C_VOICE_LEG_ON				8
#define				C_VOICE_LEG_OFF				9
#define				C_VOICE_LEFT_FANSHENG_ON	10
#define				C_VOICE_LEFT_FANSHENG_OFF	11
#define				C_VOICE_RIGHT_FANSHENG_ON	12
#define				C_VOICE_RIGHT_FANSHENG_OFF	13
#define				C_VOICE_AUTO_FANSHENG_ON	14
#define				C_VOICE_AUTO_FANSHENG_OFF	15
#define				C_VOICE_OFF					16
#define				C_VOICE_ON					17
#define				C_VOICE_ALARM_OFF			18
#define				C_VOICE_LOCK_ON				19
#define				C_VOICE_LOCK_OFF			20
#define				C_VOICE_PRESSURE_UP			21
#define				C_VOICE_PRESSURE_DOWN		22
#define				C_VOICE_10M					23
#define				C_VOICE_15M					24
#define				C_VOICE_20M					25
#define				C_VOICE_BP_DIDI				26
/************************ IO ************************************/
/************************ work ************************************/
#if				C_DEBUG_MODE
	#define				  	C_120_M					120//20分钟
	#define				  	C_90_M					200
	#define				  	C_20_M					60//20分钟
	#define				  	C_15_M					40//15分钟
	#define				  	C_10_M					30//10分钟
	
	#define				  	C_10_M					30//10分钟
	#define				  	C_7_M_5					20//7.5分钟
	#define				  	C_5_M					15//5分钟
	#define				  	C_4_M					120//4分钟
	
	#define				  	C_60S					10//1分钟
	#define				  	C_10S					10//
	#define				  	C_AutoModeCycle			120
	#define				  	C_AutoModeZuoON			30
	#define				  	C_AutoModeZuoOFF		30
	#define				  	C_AutoModeYouON			30
#else
	#define				  	C_90_M					5400//90分钟
	#define				  	C_120_M					7200//120分钟
	
	#define				  	C_20_M					1200//20分钟
	#define				  	C_15_M					900//15分钟
	#define				  	C_10_M					600//10分钟
	#define				  	C_10_M					600//10分钟
	#define				  	C_7_M_5					450//7.5分钟
	#define				  	C_5_M					300//5分钟
	#define				  	C_4_M					240//4分钟
	
	#define				  	C_60S					60//1分钟
	#define				  	C_10S					10//
	
	#define				  	C_AutoModeCycle			7200
	#define				  	C_AutoModeZuoON			1200
	#define				  	C_AutoModeZuoOFF		3600
	#define				  	C_AutoModeYouON			4800
	
	/*#define				  	C_AutoModeCycle			2400
	#define				  	C_AutoModeZuoON			600
	#define				  	C_AutoModeZuoOFF		1200
	#define				  	C_AutoModeYouON			1800*/
	
#endif
/************************ work ************************************/
/****************************** AIP650 *****************************/
/*#define	        	P_SCLK     						_pd1
#define	        	P_DIN	    			 		_pc2

#define				C_CommandDisplayOff	 			0x4800			//  ???
#define				C_CommandDisplayOn	 			0x4801 			//  ???,8???,8???
#define				C_CommandDisplayOn_1			0x4811			//  ???,8???,1???
#define				C_CommandDisplayOn_2			0x4821			//  ???,8???,2???
#define				C_CommandDisplayOn_3			0x4831			//  ???,8???,3???
#define				C_CommandDisplayOn_4			0x4841			//  ???,8???,4???
#define				C_CommandDisplayOn_5			0x4851			//  ???,8???,5???
#define				C_CommandDisplayOn_6			0x4861			//  ???,8???,6???
#define				C_CommandDisplayOn_7			0x4871			//  ???,8???,7???

#define				C_CommandDIG0					0x68			//  DIG0??,1 ON,0 OFF
#define				C_CommandDIG1					0x6A			//  DIG1??,1 ON,0 OFF
#define				C_CommandDIG2					0x6C			//  DIG2??,1 ON,0 OFF
#define				C_CommandDIG3					0x6E*/			//  DIG3??,1 ON,0 OFF
/****************************** AIP650 *****************************/

/***************** AIP1628 *****************************/

//#define				C_ComDisplayHalfOn 				0x89 
//B7 B6 B5 B4 B3 B2 B1 B0 功能 说明
//1 0 
//无关项，
//写 0 
//— 0 0 0 
//显示亮度设置
//设置脉冲宽度为 1/16
//1 0 — 0 0 1 设置脉冲宽度为 2/16
//1 0 — 0 1 0 设置脉冲宽度为 4/16
//1 0 — 0 1 1 设置脉冲宽度为 10/16
//1 0 — 1 0 0 设置脉冲宽度为 11/16
//1 0 — 1 0 1 设置脉冲宽度为 12/16
//1 0 — 1 1 0 设置脉冲宽度为 13/16
//1 0 — 1 1 1 设置脉冲宽度为 14/16
//1 0 0 — — — 显示开关设置 显示关
//1 0 1 — — — 显示开
/***************** AIP1628  *****************************/

#define				C_CAL_DATA1_EE1_ADD1				0x10
#define				C_CAL_DATA1_EE1_ADD2				0x11
#define				C_CAL_DATA1_CHECK_EE1_ADD			0x12
#define				C_CAL_DATA1_EE2_ADD1				0x13
#define				C_CAL_DATA1_EE2_ADD2				0x14
#define				C_CAL_DATA1_CHECK_EE2_ADD			0x15


#define				C_CAL_DATA2_EE1_ADD1				0x16
#define				C_CAL_DATA2_EE1_ADD2				0x17
#define				C_CAL_DATA2_CHECK_EE1_ADD			0x18
#define				C_CAL_DATA2_EE2_ADD1				0x19
#define				C_CAL_DATA2_EE2_ADD2				0x1A
#define				C_CAL_DATA2_CHECK_EE2_ADD			0x1B

//#define				C_CAL_DATA3_EE1_ADD1				0x1C
//#define				C_CAL_DATA3_EE1_ADD2				0x1D
//#define				C_CAL_DATA3_CHECK_EE1_ADD			0x1E
//#define				C_CAL_DATA3_EE2_ADD1				0x1F
//#define				C_CAL_DATA3_EE2_ADD2				0x20
//#define				C_CAL_DATA3_CHECK_EE2_ADD			0x21
//
//#define				C_CAL_DATA4_EE1_ADD1				0x22
//#define				C_CAL_DATA4_EE1_ADD2				0x23
//#define				C_CAL_DATA4_CHECK_EE1_ADD			0x24
//#define				C_CAL_DATA4_EE2_ADD1				0x25
//#define				C_CAL_DATA4_EE2_ADD2				0x26
//#define				C_CAL_DATA4_CHECK_EE2_ADD			0x27

#define				C_ZERO_DATA1_EE1_ADD1				0x28
#define				C_ZERO_DATA1_EE1_ADD2				0x29
#define				C_ZERO_DATA1_CHECK_EE1_ADD			0x2A
#define				C_ZERO_DATA1_EE2_ADD1				0x2B
#define				C_ZERO_DATA1_EE2_ADD2				0x2C
#define				C_ZERO_DATA1_CHECK_EE2_ADD			0x2D

#define				C_ZERO_DATA2_EE1_ADD1				0x30
#define				C_ZERO_DATA2_EE1_ADD2				0x31
#define				C_ZERO_DATA2_CHECK_EE1_ADD			0x32
#define				C_ZERO_DATA2_EE2_ADD1				0x33
#define				C_ZERO_DATA2_EE2_ADD2				0x34
#define				C_ZERO_DATA2_CHECK_EE2_ADD			0x35

#define				C_RF_ID_EE_ADD1						0x40
#define				C_RF_ID_EE_ADD2						0x43

#endif 