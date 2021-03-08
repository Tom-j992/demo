#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include "delay.h"
#define IIC_SCL				PAout(6)	//时钟线
#define	IIC_IN_SDA		PAin(7)   //数据线输入
#define IIC_OUT_SDA		PAout(7)	//数据线输出
void	IIC_IO_Init(u8 mode);			//mode	1.所有，2.数据线输出，3.数据线输入
void	IIC_start(void);					//起始信号
void	IIC_stop(void);					 	//停止信号
void	IIC_ack(void);					 	//应答
void	IIC_nack(void);					 	//不应答
void  IIC_wait_ack(void);				//等待应答/检测应答
void	IIC_sand_byte(u8 byte);		//发送一个字节
u8	IIC_read_byte(void);				//接收一个字节
#endif



