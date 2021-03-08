#ifndef __NEC_H
#define __NEC_H
#include "delay.h"
#include "sys.h"
#define	 delay8_77us()	delay_us(8)							//延时高电平时间
#define	 delay17_53us()	delay_us(17)						//延时低电平时间
#define  NEC_TX   		 PAout(2)
#define  NEC_RX   		 PAin(3)

extern u32 Each_bit_duration[120];		// 记录每一位数据的时长
extern uint8_t  Current_bit_CNT;					// 当前红外接收的位数
extern uint8_t  Nec_Flag;  							//红外解码标志位
extern uint8_t  Mec_Code[4];					//红外码保存地点
void NEC_OUT_Init(void);//红外发送初始化函数
void NEC_IN_Init(void);	//红外输入初始化函数
void NEC_IE_code_message(u16 user_code_16bit, u8 data_code_8bit);//发送标准的红外NEC
void NEC_IE_code_message_Meidi(u8 A,u8 B ,u8 C);//发送美的R05D电控信号
void NEC_Decoding(void);	//红外解码器


/*红外编码格式

	普通：起始码+地址码16位+8位数据码+8位数据反码+结束码		一般发送一遍
	美的空调：起始码+数据码A+数据A反码+数据码B+数据B反码+数据码C+数据C反码+结束码 数据码A通常为0xb2 ABC均为8位通常发送两遍
	
		NEC_IE_code_message_Meidi(0Xb2,0X1f,0xd8);开机
		NEC_IE_code_message_Meidi(0Xb2,0X7b,0xe0);关机

*/








#endif
