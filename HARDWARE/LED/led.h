#ifndef __LED_H
#define __LED_H

#include "sys.h"
#define LED_O  PCout(13)//宏定义  
#define LED_R  PCout(14)//宏定义
#define LED_G  PCout(15)//宏定义
#define LED_IN_R  GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_14)
#define LED_IN_G  GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_15)
void LED_Init(void);//初始化函数


#endif

