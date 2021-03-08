#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"
#define DHT11_OUT_DATA  PAout(11)
#define DHT11_IN_DATA  PAin(11)
#define OUT 1
#define IN  2
extern volatile u8 RX_DHT11[5];//数据数组
void DHT11_Init(u8 mode);			//初始化温度传感器
u8 DHT11_R_data(void);				//读取数据
	

#endif

