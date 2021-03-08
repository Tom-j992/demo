#ifndef __RGBLED_H
#define __RGBLED_H
#include "sys.h"
#define R_LED  PBout(13)
#define G_LED  PBout(14)
#define B_LED  PBout(15)
#define BLACK  0					//黑色表示不发光
#define RED    1
#define GREEN  2
#define BLUE   3
#define WHITE  4					
void RGBLED_Init(void);//初始化函数
void LED_Color(u8 color);//选择全彩灯的颜色

#endif
