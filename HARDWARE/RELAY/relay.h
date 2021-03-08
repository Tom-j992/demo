#ifndef __RELAY_H
#define __RELAY_H
#include "sys.h"
#define RELAY  					PBout(13)
#define RELAY_IN  			GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_13)
void RELAY_Init(void);//³õÊ¼º¯Êý
#endif

