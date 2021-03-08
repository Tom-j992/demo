#ifndef __OLED_H
#define __OLED_H
#include "iic.h"
void OLED_W_COM(u8 com);								//写命令
void OLED_W_DAT(u8 data);									//写数据
void OLED_Init(void);										//初始化
void OLED_DISPLAY_ON(void);								//开显示
void OLED_DISPLAY_OFF(void);						//关显示
void OLED_DISPLAY_CELL(void);							//清屏
void OLED_DISPLAY_8X16(u8 row,u8 line,u8 ass);	//显示ASCII字符
void OLED_DISPLAY_8X16_string(u8 row,u8 line,u8 *data);	//显示ASCII字符串
void OLED_DISPLAY_16x16(u8 row,u8 line,u8 num);		//显示汉字
void OLED_DISPLAY_bmp(void);								//显示图片		
void OLED_DISPLAT_Number(u8 x,u16 number);						//显示数字
void OLED_CTS_DISPLAY(u16 temp, u8 rh);//节能系统  温度与继电器状态
void OLED_DISPLAT_HEX(u8 num,u32 data);						//显示十六进制数
void OLED_DISPLAY_SYSTEM(void);
/*row不超过3,显示汉字line不超过7，字母不超过15*/
#endif


