#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"
void Adc1_Init(void); 				//ADC1初始化
u16  Get_Adc1(u8 ch); 				//获得ADC1某个通道值  
#endif 
