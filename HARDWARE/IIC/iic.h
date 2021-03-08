#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include "delay.h"
#define IIC_SCL				PAout(6)	//ʱ����
#define	IIC_IN_SDA		PAin(7)   //����������
#define IIC_OUT_SDA		PAout(7)	//���������
void	IIC_IO_Init(u8 mode);			//mode	1.���У�2.�����������3.����������
void	IIC_start(void);					//��ʼ�ź�
void	IIC_stop(void);					 	//ֹͣ�ź�
void	IIC_ack(void);					 	//Ӧ��
void	IIC_nack(void);					 	//��Ӧ��
void  IIC_wait_ack(void);				//�ȴ�Ӧ��/���Ӧ��
void	IIC_sand_byte(u8 byte);		//����һ���ֽ�
u8	IIC_read_byte(void);				//����һ���ֽ�
#endif



