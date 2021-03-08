#ifndef __OLED_H
#define __OLED_H
#include "iic.h"
void OLED_W_COM(u8 com);								//д����
void OLED_W_DAT(u8 data);									//д����
void OLED_Init(void);										//��ʼ��
void OLED_DISPLAY_ON(void);								//����ʾ
void OLED_DISPLAY_OFF(void);						//����ʾ
void OLED_DISPLAY_CELL(void);							//����
void OLED_DISPLAY_8X16(u8 row,u8 line,u8 ass);	//��ʾASCII�ַ�
void OLED_DISPLAY_8X16_string(u8 row,u8 line,u8 *data);	//��ʾASCII�ַ���
void OLED_DISPLAY_16x16(u8 row,u8 line,u8 num);		//��ʾ����
void OLED_DISPLAY_bmp(void);								//��ʾͼƬ		
void OLED_DISPLAT_Number(u8 x,u16 number);						//��ʾ����
void OLED_CTS_DISPLAY(u16 temp, u8 rh);//����ϵͳ  �¶���̵���״̬
void OLED_DISPLAT_HEX(u8 num,u32 data);						//��ʾʮ��������
void OLED_DISPLAY_SYSTEM(void);
/*row������3,��ʾ����line������7����ĸ������15*/
#endif


