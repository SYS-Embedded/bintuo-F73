
#include	"ADC.h"

unsigned int Read_AdcValue(void)
{
	unsigned int u16v_AdTemp;
	
	_start =  0; //¿ªÊ¼×ª»»
	_start =  1;
	_start =  0;
	while(_adbz);
	
	u16v_AdTemp = _sadol+(_sadoh&0x0f)*256;
	
	return u16v_AdTemp;
}


////===============================================================
////void GetBattery_Level (void)
////===============================================================
void ADC_Task (void)
{
	unsigned int 	u16v_Temp;
	unsigned char 	u8v_disTemp;
	
		if(!gubv_AdcChannelSelect)
		{
			u16v_Temp = Read_AdcValue();
			if(u16v_Temp>=gu16v_AdMaxTemp2)	gu16v_AdMaxTemp2 = u16v_Temp;
			if(u16v_Temp<=gu16v_AdMinTemp2)	gu16v_AdMinTemp2 = u16v_Temp;
			gu16v_AdcValue2 += u16v_Temp;
			/*gu8v_AdSampCnt2++;
			if(gu8v_AdSampCnt2>=4)
			{
				gu8v_AdSampCnt2 = 0;
				gu16v_AdcValue2 -= gu16v_AdMaxTemp2;
				gu16v_AdcValue2 -= gu16v_AdMinTemp2;
				gu16v_AdcValue2 >>= 1;
				gubv_AbSensorAdUpdata = 1;
				gu16v_ABAdcSensor = gu16v_AdcValue2;
				gu16v_AdcValue2 = 0; //Vsensor
				gu16v_AdMaxTemp2 = 0x0000;
				gu16v_AdMinTemp2 = 0xffff;
			}*/
			gubv_AdcChannelSelect = 1;
			_sadc0 = C_ADC_CH_FUN;
		}
		else
		{
			u16v_Temp = Read_AdcValue();
			if(u16v_Temp>=gu16v_AdMaxTemp1)	gu16v_AdMaxTemp1 = u16v_Temp;
			if(u16v_Temp<=gu16v_AdMinTemp1)	gu16v_AdMinTemp1 = u16v_Temp;
			gu16v_AdcValue1 += u16v_Temp;
			gu8v_AdSampCnt1++;
			if(gu8v_AdSampCnt1>=18)
			{
				gu8v_AdSampCnt1 = 0;
				gu16v_AdcValue1 -= gu16v_AdMaxTemp1;
				gu16v_AdcValue1 -= gu16v_AdMinTemp1;
				gu16v_AdcValue1 >>= 4;
				gubv_SensorAdUpdata = 1;
				gu16v_FunAdcSensor = gu16v_AdcValue1;
				
				if(gu16v_FunAdcSensor>gu16v_FunAdcZeroData+(gu16v_Fun7P5mmHgData/4))
				{
					u16v_Temp = gu16v_FunAdcSensor-gu16v_FunAdcZeroData;
					gu8v_FunNumDisValue = u16v_Temp/gu16v_Fun7P5mmHgData;
					gu8v_NumDisTemp = u16v_Temp%gu16v_Fun7P5mmHgData;
					gu8v_FunNumDisValue = gu8v_FunNumDisValue*10+gu8v_NumDisTemp/10;
				}
				else
				{
					gu8v_FunNumDisValue = 0;
				}
				gu16v_AdcValue2 -= gu16v_AdMaxTemp2;
				gu16v_AdcValue2 -= gu16v_AdMinTemp2;
				gu16v_AdcValue2 >>= 4;
				gu16v_ABAdcSensor = gu16v_AdcValue2;
				if(gu16v_ABAdcSensor>gu16v_AbAdcZeroData+(gu16v_Ab7P5mmHgData/4))
				{
					u16v_Temp = gu16v_ABAdcSensor-gu16v_AbAdcZeroData;
					u8v_disTemp = u16v_Temp/gu16v_Ab7P5mmHgData;
					gu8v_NumDisTemp = u16v_Temp%gu16v_Ab7P5mmHgData;
					//gu8v_AbNumDisValue = u8v_disTemp*10+gu8v_NumDisTemp/10;
					gu16v_AbNumDisValueOld += u8v_disTemp*10+gu8v_NumDisTemp/10;
					gu8v_AbSensorDisCnt++;
					if(gu8v_AbSensorDisCnt>=4)
					{
						gu8v_AbSensorDisCnt = 0;
						gu8v_AbNumDisValue = gu16v_AbNumDisValueOld>>2;
						gu16v_AbNumDisValueOld = 0;
					}
				}
				else
				{
					gu8v_AbNumDisValue = 0;
				}
				
				gu16v_AdcValue2 = 0; //AB SENSOR
				gu16v_AdMaxTemp2 = 0x0000;
				gu16v_AdMinTemp2 = 0xffff;
				
				gu16v_AdcValue1 = 0; //FUN SENSOR
				gu16v_AdMaxTemp1 = 0x0000;
				gu16v_AdMinTemp1 = 0xffff;
			}
			gubv_AdcChannelSelect = 0;
			_sadc0 = C_ADC_CH_AB;	
		}
}


