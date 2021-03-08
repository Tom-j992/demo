#include "iic.h"
/*********************************************************************************************/
void	IIC_IO_Init(u8 mode)			//mode	1.���У�2.�����������3.����������
{
	GPIO_InitTypeDef GPIO_InitSTR;
	if(mode==1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
			GPIO_InitSTR.GPIO_Mode=GPIO_Mode_Out_PP;
			GPIO_InitSTR.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
			GPIO_InitSTR.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_Init(GPIOA,&GPIO_InitSTR);
			GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);
		}
		else if(mode==2)
						{
							GPIO_InitSTR.GPIO_Mode=GPIO_Mode_Out_PP;
							GPIO_InitSTR.GPIO_Pin=GPIO_Pin_7;
							GPIO_InitSTR.GPIO_Speed=GPIO_Speed_50MHz;
							GPIO_Init(GPIOA,&GPIO_InitSTR);
						}
					else if(mode==3)
									{
										GPIO_InitSTR.GPIO_Mode=GPIO_Mode_IN_FLOATING;
										GPIO_InitSTR.GPIO_Pin=GPIO_Pin_7;
										GPIO_Init(GPIOA,&GPIO_InitSTR);
									}
}
/*********************************************************************************************/
void	IIC_start(void)						//��ʼ�ź�
{	
	IIC_SCL=1;
	IIC_OUT_SDA=1;
	delay_us(5);
	IIC_OUT_SDA=0;
	delay_us(5);
	IIC_SCL=0;
}
/*********************************************************************************************/
void	IIC_stop(void)						//ֹͣ�ź�
{
	IIC_SCL=1;
	IIC_OUT_SDA=0;
	delay_us(5);
	IIC_OUT_SDA=1;
	delay_us(5);
}
/*********************************************************************************************/
void	IIC_ack(void) 						//Ӧ��
{
	IIC_OUT_SDA=0;
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
	IIC_OUT_SDA=1;
}
/*********************************************************************************************/
void	IIC_nack(void) 						//��Ӧ��
{
	IIC_OUT_SDA=1;
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
	IIC_OUT_SDA=0;
}
/*********************************************************************************************/
void  IIC_wait_ack(void)				//�ȴ�Ӧ��/���Ӧ�� 
{
	IIC_SCL=0;
	IIC_OUT_SDA=1;
	IIC_IO_Init(3);
	IIC_SCL=1;
	if(!IIC_IN_SDA)
	{
		IIC_stop();
	}
	IIC_SCL=0;
	IIC_IO_Init(2);
}
/*********************************************************************************************/
void	IIC_sand_byte(u8 byte) 		//����һ���ֽ�
{
	u8 data=8;
	IIC_SCL=0;
	while(data--)
	{
		
			if(byte&0x80)
			{
				IIC_OUT_SDA=1;
			}
			else
			{
				IIC_OUT_SDA=0;
			}
		IIC_SCL=1;
		IIC_SCL=0;
		byte<<=1;
	}
}
/*********************************************************************************************/
u8	IIC_read_byte(void) 				//����һ���ֽ�
{
	u8 data=0x00,x=8;
	IIC_IO_Init(3);
	IIC_SCL=0;
	while(x--)
	{
		
		IIC_SCL=1;
		if(!IIC_IN_SDA)
			data++;
		IIC_SCL=0;
		data<<=1;
	}
	IIC_IO_Init(2);
	return data;	
}
/*********************************************************************************************/


