 

/* Includes ------------------------------------------------------------------*/
#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "stm32f10x_adc.h"


void Adc_Battery_Init(void);
void Adc_Angle_Init(void);

u16  Get_Adc_Battery(u8 ch); 
u16 Get_Adc_Battery_Average(u8 ch,u8 times);

u16  Get_Adc_Angle(u8 ch); 
u16 Get_Adc_Angle_Average(u8 ch,u8 times);
#endif 
