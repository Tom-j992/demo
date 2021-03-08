#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#define KEY_1  PBin(0)	//绑定引脚
#define KEY_2  PBin(1)	//
void KEY_Init(void);		//初始化
u8 KEY_Scanf(void);			//按键扫描函数

#endif

