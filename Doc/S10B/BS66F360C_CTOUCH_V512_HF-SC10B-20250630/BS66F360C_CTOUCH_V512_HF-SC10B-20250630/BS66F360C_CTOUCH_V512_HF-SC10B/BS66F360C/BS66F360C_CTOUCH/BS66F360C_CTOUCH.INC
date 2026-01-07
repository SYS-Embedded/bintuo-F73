;;;;;///*********************************************************************************************************//**
;;;;;// * @file    BS66F360C_CTOUCH.INC
;;;;;// * @version V1.00
;;;;;// * @date    11/16/2020
;;;;;// * @brief   The header file of the BS66F360C_CTOUCH library.
;;;;;// *************************************************************************************************************
;;;;;// * @attention
;;;;;// * <h2><center>Copyright (C) Best Solution Inc. All rights reserved</center></h2>
;;;;;// ************************************************************************************************************/

;;;;;///* ==================================================================================================================================================*/
;;;;;///** @addtogroup BS66F360C_CTOUCH
;;;;;//  * @{
;;;;;//  */
;;;;;///* ---------------------------------------------------------------------------------------------------------*/
;;;;;//
;;;;;///* ---------------------------------------------------------------------------------------------------------*/
;;;;;///* Exported functions --------------------------------------------------------------------------------------*/
;;;;;///* ---------------------------------------------------------------------------------------------------------*/
;;;;;///** @defgroup  BS66F360C_CTOUCH include constants
;;;;;//  * @{
;;;;;//  */
;;;;;//

#define BS66F360C_CTOUCH_DEF
#include "..\GLOBE\GLOBE_VARIES.INC"
#include "..\MAIN_PROGRAM\MAIN_PROGRAM.EXT"
#include "BS66F360C_CTOUCH.DEF"

;/*--------- <<<config>>> -----------------*/
;//<include file> #include "..\BS66F360C_CTOUCH\BS66F360C_CTOUCH.INI"
;//<simple description>Simple prompt message
;//<support MCU>BS66F360C

;//******************************************************************************************
;//******************************************************************************************
;//******************************************************************************************
;//******************************************************************************************

;/*-------------------------------------------------*/
;/*-------- Touch Workshop Option ------------------*/
;/*-------------------------------------------------*/

;//******************************************************************************************
;//******************************************************************************************
;//******************************************************************************************

;//<use HardWare>TOUCH\TBC
;//<use Language>asm
;//<config Diagram Png>Touch.png
;//<associated Packages>

;//<TOUCH>__KEY1_EN
;//<ALIAS>KEY1
#define ___KEY1     PB0
#define ___KEY1_C   PBC0
#define ___KEY1_PU  PBPU0

;//<TOUCH>__KEY2_EN
;//<ALIAS>KEY2
#define ___KEY2     PB0
#define ___KEY2_C   PBC0
#define ___KEY2_PU  PBPU0

;//<TOUCH>__KEY3_EN
;//<ALIAS>KEY3
#define ___KEY3     PB0
#define ___KEY3_C   PBC0
#define ___KEY3_PU  PBPU0

;//<TOUCH>__KEY4_EN
;//<ALIAS>KEY4
#define ___KEY4     PB0
#define ___KEY4_C   PBC0
#define ___KEY4_PU  PBPU0

;//<TOUCH>__KEY5_EN
;//<ALIAS>KEY5
#define ___KEY5     PB0
#define ___KEY5_C   PBC0
#define ___KEY5_PU  PBPU0

;//<TOUCH>__KEY6_EN
;//<ALIAS>KEY6
#define ___KEY6     PB0
#define ___KEY6_C   PBC0
#define ___KEY6_PU  PBPU0

;//<TOUCH>__KEY7_EN
;//<ALIAS>KEY7
#define ___KEY7     PB0
#define ___KEY7_C   PBC0
#define ___KEY7_PU  PBPU0

;//<TOUCH>__KEY8_EN
;//<ALIAS>KEY8
#define ___KEY8     PB0
#define ___KEY8_C   PBC0
#define ___KEY8_PU  PBPU0

;//<TOUCH>__KEY9_EN
;//<ALIAS>KEY9
#define ___KEY9     PB0
#define ___KEY9_C   PBC0
#define ___KEY9_PU  PBPU0

;//<TOUCH>__KEY10_EN
;//<ALIAS>KEY10
#define ___KEY10     PB0
#define ___KEY10_C   PBC0
#define ___KEY10_PU  PBPU0

;//<TOUCH>__KEY11_EN
;//<ALIAS>KEY11
#define ___KEY11     PB0
#define ___KEY11_C   PBC0
#define ___KEY11_PU  PBPU0

;//<TOUCH>__KEY12_EN
;//<ALIAS>KEY12
#define ___KEY12     PB0
#define ___KEY12_C   PBC0
#define ___KEY12_PU  PBPU0

;//<TOUCH>__KEY13_EN
;//<ALIAS>KEY13
#define ___KEY13     PB0
#define ___KEY13_C   PBC0
#define ___KEY13_PU  PBPU0

;//<TOUCH>__KEY14_EN
;//<ALIAS>KEY14
#define ___KEY14     PB0
#define ___KEY14_C   PBC0
#define ___KEY14_PU  PBPU0

;//<TOUCH>__KEY15_EN
;//<ALIAS>KEY15
#define ___KEY15     PB0
#define ___KEY15_C   PBC0
#define ___KEY15_PU  PBPU0

;//<TOUCH>__KEY16_EN
;//<ALIAS>KEY16
#define ___KEY16     PB0
#define ___KEY16_C   PBC0
#define ___KEY16_PU  PBPU0

;//<TOUCH>__KEY17_EN
;//<ALIAS>KEY17
#define ___KEY17     PB0
#define ___KEY17_C   PBC0
#define ___KEY17_PU  PBPU0

;//<TOUCH>__KEY18_EN
;//<ALIAS>KEY18
#define ___KEY18     PB0
#define ___KEY18_C   PBC0
#define ___KEY18_PU  PBPU0

;//<TOUCH>__KEY19_EN
;//<ALIAS>KEY19
#define ___KEY19     PB0
#define ___KEY19_C   PBC0
#define ___KEY19_PU  PBPU0

;//<TOUCH>__KEY20_EN
;//<ALIAS>KEY20
#define ___KEY20     PB0
#define ___KEY20_C   PBC0
#define ___KEY20_PU  PBPU0

;//<TOUCH>__KEY21_EN
;//<ALIAS>KEY21
#define ___KEY21     PB0
#define ___KEY21_C   PBC0
#define ___KEY21_PU  PBPU0

;//<TOUCH>__KEY22_EN
;//<ALIAS>KEY22
#define ___KEY22     PB0
#define ___KEY22_C   PBC0
#define ___KEY22_PU  PBPU0

;//<TOUCH>__KEY23_EN
;//<ALIAS>KEY23
#define ___KEY23     PB0
#define ___KEY23_C   PBC0
#define ___KEY23_PU  PBPU0

;//<TOUCH>__KEY24_EN
;//<ALIAS>KEY24
#define ___KEY24     PB0
#define ___KEY24_C   PBC0
#define ___KEY24_PU  PBPU0

;//<TOUCH>__KEY25_EN
;//<ALIAS>KEY25
#define ___KEY25     PB0
#define ___KEY25_C   PBC0
#define ___KEY25_PU  PBPU0

;//<TOUCH>__KEY26_EN
;//<ALIAS>KEY26
#define ___KEY26     PB0
#define ___KEY26_C   PBC0
#define ___KEY26_PU  PBPU0

;//<TOUCH>__KEY27_EN
;//<ALIAS>KEY27
#define ___KEY27     PB0
#define ___KEY27_C   PBC0
#define ___KEY27_PU  PBPU0

;//<TOUCH>__KEY28_EN
;//<ALIAS>KEY28
#define ___KEY28     PB0
#define ___KEY28_C   PBC0
#define ___KEY28_PU  PBPU0

;/*-------- <<<\config>>> ----------------*/



;/*-------- <<<globe>>> ------------------*/
  ifndef TouchLibraryVersion
      #define TouchLibraryVersion     512H
  endif
;/*-------- <<<\globe>>> ------------------*/

ifndef  ___CTOUCH_WORKSHOP
#define ___CTOUCH_WORKSHOP

;/*-------- <<<option>>> ------------------*/
;// <h> TKL_Config
    
      ;// <o> DebounceTimes
      ;// <i> Debounce in output key status 
      ;// <0-15>
      #define DebounceTimes           0

      ;// <o> AutoCalibrationPeriod
      ;// <i> auto calibration period select 80ms to 1280ms.The faster speed the better the anti-interference and the worse the sensitivity.The slower speed the worse the anti-interference and the better the sensitivity
      ;// <0 =>     80mS    
      ;// <1 =>    160mS
      ;// <2 =>    240mS
      ;// <3 =>    320mS
      ;// <4 =>    400mS
      ;// <5 =>    480mS
      ;// <6 =>    560mS
      ;// <7 =>    640mS
      ;// <8 =>    720mS
      ;// <9 =>    800mS
      ;// <10=>    880mS
      ;// <11=>    960mS
      ;// <12=>   1040mS
      ;// <13=>   1120mS
      ;// <14=>   1200mS
      ;// <15=>   1280mS
      #define  AutoCalibrationPeriod  7

      ;// <o> HighSensitive 
      ;// <i> Sensitive double up,0-Normal  1-High Sensitive
      ;// <0=>     Normal
      ;// <1=>     High
      #define HighSensitive           1

      ;// <o> MaximumKeyHoldTime 
      ;// <i> key holding time ,if time out will reset key status to non-press,Range is 4S~60S or Disable the function
      ;// <0 =>  Disable    
      ;// <1 =>       4S
      ;// <2 =>       8S
      ;// <3 =>      12S
      ;// <4 =>      16S
      ;// <5 =>      20S
      ;// <6 =>      24S
      ;// <7 =>      28S
      ;// <8 =>      32S
      ;// <9 =>      36S
      ;// <10=>      40S
      ;// <11=>      44S
      ;// <12=>      48S
      ;// <13=>      52S
      ;// <14=>      56S
      ;// <15=>      60S
      #define  MaximumKeyHoldTime     2

      ;// <q> AutoFrequencyHopping
      ;// <i> enalbe hardware hopping function     
      #define AutoFrequencyHopping    1
      
      
      ;// <q> OneKeyActive
      ;// <i> Only one or all key active at the same time
      ;// <0 =>  all key active    
      ;// <1 =>  one key active
      #define OneKeyActive            1

      ;// <q> PowerSave
      ;// <i> Low power mode 
      #define PowerSave               0
  
      ;// <q> TKL_MovingCalibration
      ;// <i> Touch key Moving Calibration keys easier to operate
      #define MovingCalibration       1
      
      ;// <q> MainFreqSelect
      ;// <i> Touch frequency selection
      ;// <0 =>  Normal
      ;// <1 =>  High
      ;// <2 =>  Low
      #define MainFreqSelect          0

   ;// </h>
  
  ;// <h> TKL_ENABLE_KEY
      
    ;// <i> If the setting over the maximum key, it will be set disable
    
    ;// <e> __KEY1_EN
      ;// <i> 0=__KEY1 disable 1=__KEY1 enalbe 
        #define __KEY1_EN                 1
      ;// <o> Key1Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key1Threshold            16
      ;// <o> __KEY1_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY1_WAKE               0
    ;// </e>
    
    ;// <e> __KEY2_EN
      ;// <i> 0=__KEY2 disable 1=__KEY2 enalbe 
        #define __KEY2_EN                 1
      ;// <o> Key2Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key2Threshold            16
      ;// <o> __KEY2_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY2_WAKE               0
    ;// </e>
    
    ;// <e> __KEY3_EN
      ;// <i> 0=__KEY3 disable 1=__KEY3 enalbe 
        #define __KEY3_EN                 1
      ;// <o> Key3Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key3Threshold            16
      ;// <o> __KEY3_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY3_WAKE               0
    ;// </e>
    
    ;// <e> __KEY4_EN
      ;// <i> 0=__KEY4 disable 1=__KEY4 enalbe 
        #define __KEY4_EN                 1
      ;// <o> Key4Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key4Threshold            16
      ;// <o> __KEY4_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY4_WAKE               0
    ;// </e>
    
    ;// <e> __KEY5_EN
      ;// <i> 0=__KEY5 disable 1=__KEY5 enalbe 
        #define __KEY5_EN                 1
      ;// <o> Key5Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key5Threshold            16
      ;// <o> __KEY5_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY5_WAKE               0
    ;// </e>
    
    ;// <e> __KEY6_EN
      ;// <i> 0=__KEY6 disable 1=__KEY6 enalbe 
        #define __KEY6_EN                 1
      ;// <o> Key6Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key6Threshold            16
      ;// <o> __KEY6_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY6_WAKE               0
    ;// </e>
    
    ;// <e> __KEY7_EN
      ;// <i> 0=__KEY7 disable 1=__KEY7 enalbe 
        #define __KEY7_EN                 1
      ;// <o> Key7Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key7Threshold            16
      ;// <o> __KEY7_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY7_WAKE               0
    ;// </e>
    
    ;// <e> __KEY8_EN
      ;// <i> 0=__KEY8 disable 1=__KEY8 enalbe 
        #define __KEY8_EN                 1
      ;// <o> Key8Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key8Threshold            16
      ;// <o> __KEY8_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY8_WAKE               0
    ;// </e>
    
    ;// <e> __KEY9_EN
      ;// <i> 0=__KEY9 disable 1=__KEY9 enalbe 
        #define __KEY9_EN                 1
      ;// <o> Key9Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key9Threshold            16
      ;// <o> __KEY9_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY9_WAKE               0
    ;// </e>
    
    ;// <e> __KEY10_EN
      ;// <i> 0=__KEY10 disable 1=__KEY10 enalbe 
        #define __KEY10_EN                 1
      ;// <o> Key10Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key10Threshold            16
      ;// <o> __KEY10_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY10_WAKE               0
    ;// </e>
    
    ;// <e> __KEY11_EN
      ;// <i> 0=__KEY11 disable 1=__KEY11 enalbe 
        #define __KEY11_EN                 1
      ;// <o> Key11Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key11Threshold            16
      ;// <o> __KEY11_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY11_WAKE               0
    ;// </e>
    
    ;// <e> __KEY12_EN
      ;// <i> 0=__KEY12 disable 1=__KEY12 enalbe 
        #define __KEY12_EN                 1
      ;// <o> Key12Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key12Threshold            16
      ;// <o> __KEY12_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY12_WAKE               0
    ;// </e>
    
    ;// <e> __KEY13_EN
      ;// <i> 0=__KEY13 disable 1=__KEY13 enalbe 
        #define __KEY13_EN                 1
      ;// <o> Key13Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key13Threshold            16
      ;// <o> __KEY13_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY13_WAKE               0
    ;// </e>
    
    ;// <e> __KEY14_EN
      ;// <i> 0=__KEY14 disable 1=__KEY14 enalbe 
        #define __KEY14_EN                 1
      ;// <o> Key14Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key14Threshold            16
      ;// <o> __KEY14_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY14_WAKE               0
    ;// </e>
    
    ;// <e> __KEY15_EN
      ;// <i> 0=__KEY15 disable 1=__KEY15 enalbe 
        #define __KEY15_EN                 1
      ;// <o> Key15Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key15Threshold            16
      ;// <o> __KEY15_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY15_WAKE               0
    ;// </e>
    
    ;// <e> __KEY16_EN
      ;// <i> 0=__KEY16 disable 1=__KEY16 enalbe 
        #define __KEY16_EN                 1
      ;// <o> Key16Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key16Threshold            16
      ;// <o> __KEY16_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY16_WAKE               0
    ;// </e>
    
    ;// <e> __KEY17_EN
      ;// <i> 0=__KEY17 disable 1=__KEY17 enalbe 
        #define __KEY17_EN                 1
      ;// <o> Key17Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key17Threshold            16
      ;// <o> __KEY17_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY17_WAKE               0
    ;// </e>
    
    ;// <e> __KEY18_EN
      ;// <i> 0=__KEY18 disable 1=__KEY18 enalbe 
        #define __KEY18_EN                 1
      ;// <o> Key18Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key18Threshold            16
      ;// <o> __KEY18_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY18_WAKE               0
    ;// </e>
    
    ;// <e> __KEY19_EN
      ;// <i> 0=__KEY19 disable 1=__KEY19 enalbe 
        #define __KEY19_EN                 1
      ;// <o> Key19Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key19Threshold            16
      ;// <o> __KEY19_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY19_WAKE               0
    ;// </e>
    
    ;// <e> __KEY20_EN
      ;// <i> 0=__KEY20 disable 1=__KEY20 enalbe 
        #define __KEY20_EN                 1
      ;// <o> Key20Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key20Threshold            16
      ;// <o> __KEY20_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY20_WAKE               0
    ;// </e>
    
    ;// <e> __KEY21_EN
      ;// <i> 0=__KEY21 disable 1=__KEY21 enalbe 
        #define __KEY21_EN                 1
      ;// <o> Key21Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key21Threshold            16
      ;// <o> __KEY21_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY21_WAKE               0
    ;// </e>
    
    ;// <e> __KEY22_EN
      ;// <i> 0=__KEY22 disable 1=__KEY22 enalbe 
        #define __KEY22_EN                 1
      ;// <o> Key22Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key22Threshold            16
      ;// <o> __KEY22_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY22_WAKE               0
    ;// </e>
    
    ;// <e> __KEY23_EN
      ;// <i> 0=__KEY23 disable 1=__KEY23 enalbe 
        #define __KEY23_EN                 1
      ;// <o> Key23Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key23Threshold            16
      ;// <o> __KEY23_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY23_WAKE               0
    ;// </e>
    
    ;// <e> __KEY24_EN
      ;// <i> 0=__KEY24 disable 1=__KEY24 enalbe 
        #define __KEY24_EN                 1
      ;// <o> Key24Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key24Threshold            16
      ;// <o> __KEY24_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY24_WAKE               0
    ;// </e>
    
    ;// <e> __KEY25_EN
      ;// <i> 0=__KEY25 disable 1=__KEY25 enalbe 
        #define __KEY25_EN                 1
      ;// <o> Key25Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key25Threshold            16
      ;// <o> __KEY25_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY25_WAKE               0
    ;// </e>
    
    ;// <e> __KEY26_EN
      ;// <i> 0=__KEY26 disable 1=__KEY26 enalbe 
        #define __KEY26_EN                 1
      ;// <o> Key26Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key26Threshold            16
      ;// <o> __KEY26_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY26_WAKE               0
    ;// </e>
    
    ;// <e> __KEY27_EN
      ;// <i> 0=__KEY27 disable 1=__KEY27 enalbe 
        #define __KEY27_EN                 1
      ;// <o> Key27Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key27Threshold            16
      ;// <o> __KEY27_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY27_WAKE               0
    ;// </e>
    
    ;// <e> __KEY28_EN
      ;// <i> 0=__KEY28 disable 1=__KEY28 enalbe 
        #define __KEY28_EN                 1
      ;// <o> Key28Threshold
      ;// <i> suggestion range 12 ~ 63
      ;// <12-63>
        #define Key28Threshold            16
      ;// <o> __KEY28_WAKE
      ;// <i> sleep mode work Touch 
      ;// <0=>     Enable
      ;// <1=>     Disable
        #define __KEY28_WAKE               0
    ;// </e>
  ;// </h> 

    #define IO_TOUCH_ATTR_IP0   ((__KEY1_EN<<0|__KEY2_EN<<1|__KEY3_EN<<2|__KEY4_EN<<3))
    #define IO_TOUCH_ATTR_IP1   ((__KEY5_EN<<0|__KEY6_EN<<1|__KEY7_EN<<2|__KEY8_EN<<3)<<4)
    #define IO_TOUCH_ATTR_IP2   ((__KEY9_EN<<0|__KEY10_EN<<1|__KEY11_EN<<2|__KEY12_EN<<3)<<8)
    #define IO_TOUCH_ATTR_IP3   ((__KEY13_EN<<0|__KEY14_EN<<1|__KEY15_EN<<2|__KEY16_EN<<3)<<12)
    #define IO_TOUCH_ATTR_IP4   ((__KEY17_EN<<0|__KEY18_EN<<1|__KEY19_EN<<2|__KEY20_EN<<3)<<16)
    #define IO_TOUCH_ATTR_IP5   ((__KEY21_EN<<0|__KEY22_EN<<1|__KEY23_EN<<2|__KEY24_EN<<3)<<20)
    #define IO_TOUCH_ATTR_IP6   ((__KEY25_EN<<0|__KEY26_EN<<1|__KEY27_EN<<2|__KEY28_EN<<3)<<24)
    #define IO_TOUCH_ATTR       (IO_TOUCH_ATTR_IP0|IO_TOUCH_ATTR_IP1|IO_TOUCH_ATTR_IP2|IO_TOUCH_ATTR_IP3|IO_TOUCH_ATTR_IP4|IO_TOUCH_ATTR_IP5|IO_TOUCH_ATTR_IP6)
      
    #define WAKEUP_KEY_IP0      (((__KEY1_WAKE^1)<<0|(__KEY2_WAKE^1)<<1|(__KEY3_WAKE^1)<<2|(__KEY4_WAKE^1)<<3))
    #define WAKEUP_KEY_IP1      (((__KEY5_WAKE^1)<<0|(__KEY6_WAKE^1)<<1|(__KEY7_WAKE^1)<<2|(__KEY8_WAKE^1)<<3)<<4)
    #define WAKEUP_KEY_IP2      (((__KEY9_WAKE^1)<<0|(__KEY10_WAKE^1)<<1|(__KEY11_WAKE^1)<<2|(__KEY12_WAKE^1)<<3)<<8)
    #define WAKEUP_KEY_IP3      (((__KEY13_WAKE^1)<<0|(__KEY14_WAKE^1)<<1|(__KEY15_WAKE^1)<<2|(__KEY16_WAKE^1)<<3)<<12)
    #define WAKEUP_KEY_IP4      (((__KEY17_WAKE^1)<<0|(__KEY18_WAKE^1)<<1|(__KEY19_WAKE^1)<<2|(__KEY20_WAKE^1)<<3)<<16)
    #define WAKEUP_KEY_IP5      (((__KEY21_WAKE^1)<<0|(__KEY22_WAKE^1)<<1|(__KEY23_WAKE^1)<<2|(__KEY24_WAKE^1)<<3)<<20)
    #define WAKEUP_KEY_IP6      (((__KEY25_WAKE^1)<<0|(__KEY26_WAKE^1)<<1|(__KEY27_WAKE^1)<<2|(__KEY28_WAKE^1)<<3)<<24)
    #define WAKEUP_KEY          (WAKEUP_KEY_IP0|WAKEUP_KEY_IP1|WAKEUP_KEY_IP2|WAKEUP_KEY_IP3|WAKEUP_KEY_IP4|WAKEUP_KEY_IP5|WAKEUP_KEY_IP6)
    
;/*-------- <<<\option>>> ------------------*/

endif

;;;;;///* --------------------------------------------------------------------- */
;;;;;///**
;;;;;//  * @}
;;;;;//  */
;;;;;///* ---------------------------------------------------------------------------------------------------------*/
;;;;;///**
;;;;;//  * @}
;;;;;//  */
;;;;;///* ==================================================================================================================================================*/



