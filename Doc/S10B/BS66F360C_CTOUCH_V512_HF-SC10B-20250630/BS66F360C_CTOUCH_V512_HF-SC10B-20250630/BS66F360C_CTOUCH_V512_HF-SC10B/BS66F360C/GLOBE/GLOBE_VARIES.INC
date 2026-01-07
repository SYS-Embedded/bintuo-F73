;;;;;/*********************************************************************************************************//**
;;;;; * @file    CALCULATE_POSITION.INC
;;;;; * @version V1.00
;;;;; * @date    11/13/2020
;;;;; * @brief   The header file of the CALCULATE_POSITION library.
;;;;; *************************************************************************************************************
;;;;; * @attention
;;;;; * <h2><center>Copyright (C) Best Solution Inc. All rights reserved</center></h2>
;;;;; ************************************************************************************************************/

;;;;;/* Includes ------------------------------------------------------------------------------------------------*/
;;;;;;////******************************************
;;;;;;////****TKS GLOBE VARIES DEFINE FOR ASM CODE *
;;;;;;////******************************************
;;;;;;//-DEFINE LIBRARY VERSION
#define TouchLibraryVersion              512H
#define _CCV3_
#include "..\DEVICE\BS66F360C.DEV"
#define ___CTOUCH_WORKSHOP
;;;;;/* ==================================================================================================================================================*/

;;;;;/** @addtogroup CALCULATE_POSITION
;;;;;  * @{
;;;;;  */
;;;;;/* ---------------------------------------------------------------------------------------------------------*/
;;;;;/* Exported functions --------------------------------------------------------------------------------------*/
;;;;;/* ---------------------------------------------------------------------------------------------------------*/
;;;;;/** @defgroup  CALCULATE_POSITION_exported_functions CALCULATE_POSITION exported functions
;;;;;  * @{
;;;;;  */
;;;;;
;;;;;/* ---------------------------------------------------------------------- */
;;;;;/* assembly exported function,register                                    */
;;;;;/* ---------------------------------------------------------------------- */
;;;;;/*
;;;;;;-SUBROUTIN
;#include "..\DEVICE\BS66F360C.DEV"

;;;;;//------------------------
;;;;;//-DEFINE SYSTEM CLOCK   -
;;;;;//------------------------
#define SystemClock             2       ;;;;;//0=8MHZ
                                        ;;;;;//1=12MHZ
                                        ;;;;;//2=16MHZ
;;;;;//--------------------------------
;;;;;//-TOUCH KEY LIBRARY VARIES DEFINE
;;;;;//--------------------------------
#define CTOUCH_V512_DEF
;;;;;//-numeric operate  range 0 ~ 15;//
#define DebounceTimes           0

;;;;;//-numeric operate : range 0 ~ 15;// function: Time period to calibrate
#define AutoCalibrationPeriod   7   ;;;;;//auto calibration period select 0=80ms .....15=1280ms

;;;;;//-bit operate                 : function: Sensitive double up
#define HighSensitive           0   ;;;;;//0=Normal ;// 1=High Sensitive

;;;;;//-numeric operate ;// range 0 ~ 15: function: key holding time ,if time out will reset key status to non-press
#define MaximumKeyHoldTime      2   ;;;;;//0=disable ;// 1=4 secend ...... 15=60secend

;;;;;//-bit operate ;// range 0/1   : function: enalbe hardware hopping function
#define AutoFrequencyHopping    0   ;;;;;//0=disable ;// 1=enable

;;;;;//-bit operate ;// range 0/1   : function: only one or all key active at the same time
#define OneKeyActive            1   ;;;;;//0=all key active ;// 1=one key active

;;;;;//-bit operate ;// range 0/1   : function: Low power consumption
#define PowerSave               0   ;;;;;//0=disable ;// 1=power save mode

;;;;;//-bit operate ;// range 0/1   : function: moving calibration signal whatever key press or not
#define MovingCalibration       1   ;;;;;//0=calibrate when key non press  ;// 1=enable calibration whatever key press or not

;;;;;//-numeric operate ;// range 0 ~ 2 : function: Main frequency selection
#define MainFreqSelect          2   ;;;;;//0:3M/7M  1:3M/11M 2:3M/1M

;;;;;//-Key threshold define
#define Key1Threshold           25     ;;;;;//suggestion range 10 ~ 64
#define Key2Threshold           25
#define Key3Threshold           25
#define Key4Threshold           25
;;;;;//--
#define Key5Threshold           25
#define Key6Threshold           25
#define Key7Threshold           25
#define Key8Threshold           25
;;;;;//--
#define Key9Threshold           25
#define Key10Threshold          25
#define Key11Threshold          25
#define Key12Threshold          25
;;;;;//--
#define Key13Threshold          25
#define Key14Threshold          25
#define Key15Threshold          25
#define Key16Threshold          25
;;;;;//--
#define Key17Threshold          25
#define Key18Threshold          25
#define Key19Threshold          25
#define Key20Threshold          25
;;;;;//--
#define Key21Threshold          25
#define Key22Threshold          25
#define Key23Threshold          25
#define Key24Threshold          25
;;;;;//--
#define Key25Threshold          25
#define Key26Threshold          25
#define Key27Threshold          25
#define Key28Threshold          25
;;;;;//--
;;;;;//---------------------------------
;;;;;//-DEFINE PIN AS I/O OR TOUCH INPUT
;;;;;//---------------------------------
#define IO_TOUCH_ATTR           00000000011111111110111111001111B;;;;;//0=IO ;// 1=TOUCH INPUT
                     ;;;;;//KEY 3   ~   2 ~ 2 ~ 1 ~ 1 ~ 0 ~ 0 ~0 ;//KEY32~KEY1
                     ;;;;;//    2       4   0   6   2   8   4  1


;//---------------------------------
;//-DEFINE WAKEUP KEY                     
;//---------------------------------
#define WAKEUP_KEY              00000000000000000000000000000000B;//0=DISABLE ; 1=ENABLE
                         ;//KEY 3   ~   2 ~ 2 ~ 1 ~ 1 ~ 0 ~ 0 ~0 ;KEY32~KEY1
                         ;//    2       4   0   6   2   8   4  1

#define IIC_ADDRESS    	0A0H
#define IIC_SDA_PU  	SET PBPU.0
#define IIC_SCL_PU  	SET	PBPU.1
#define IIC_SDA_PIN 	IIC_SDA_ON_PB0
#define IIC_SCL_PIN 	IIC_SCL_ON_PB1


;;;;;;-FLAG DEFINE
;;;;;*/
;;;;;//--------------------------------------------------------------------------
;;;;;
;;;;;/* ---------------------------------------------------------------------- */
;;;;;/* C exported function,register                                           */
;;;;;/* ---------------------------------------------------------------------- */
;;;;;/*

ifdef _INCLUDE_C_
*/
//---------------------------------------------------------------
//#include "DEVICE\BS66F360C.DEV"

//---------------------------------------------------------------
#ifdef  _CCV3_
//;-_CCV3_
#else
//;-_CCV2_
#endif
//---------------------------------------------------------------
/*
endif
;;;;;*/


;;;;;/* ---------------------------------------------------------------------- */
;;;;;/**
;;;;;  * @}
;;;;;  */
;;;;;/* ---------------------------------------------------------------------------------------------------------*/
;;;;;/**
;;;;;  * @}
;;;;;  */
;;;;;/* ==================================================================================================================================================*/




