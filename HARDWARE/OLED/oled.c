#include "oled.h"
#include "ascii.h"
#include "hanzhi.h"
#include "bmp.h"
#include "dht11.h"
#include "wifi.h"
/******************************************************************************************************/
void OLED_W_COM(u8 com) 								//写命令
{
	IIC_start();
	IIC_sand_byte(0X78);
	IIC_wait_ack();
	IIC_sand_byte(0X00);
	IIC_wait_ack();
	IIC_sand_byte(com);
	IIC_wait_ack();
	IIC_stop();
}
/******************************************************************************************************/
void OLED_W_DAT(u8 data)									//写数据
{
	IIC_start();
	IIC_sand_byte(0X78);
	IIC_wait_ack();
	IIC_sand_byte(0X40);
	IIC_wait_ack();
	IIC_sand_byte(data);
	IIC_wait_ack();
	IIC_stop();
}
/******************************************************************************************************/
void OLED_Init(void)										//初始化
{
		delay_ms(100);
		OLED_W_COM(0Xae);
   	OLED_W_COM(0X00);
		OLED_W_COM(0X10);     
		OLED_W_COM(0Xd5);
		OLED_W_COM(0X80); 
		OLED_W_COM(0Xa8);
		OLED_W_COM(0X3f);	
		OLED_W_COM(0Xd3);
		OLED_W_COM(0X00);	
		OLED_W_COM(0XB0);	
		OLED_W_COM(0X40);	
		OLED_W_COM(0X8d);
		OLED_W_COM(0X14);
		OLED_W_COM(0Xa1);
		OLED_W_COM(0Xc8);
		OLED_W_COM(0Xda);
		OLED_W_COM(0X12); 
		OLED_W_COM(0X81);
		OLED_W_COM(0Xff);
		OLED_W_COM(0Xd9);
		OLED_W_COM(0Xf1); 
		OLED_W_COM(0Xdb);
		OLED_W_COM(0X30);	
		OLED_W_COM(0X20);
		OLED_W_COM(0X00);	
		OLED_W_COM(0Xa4);	
		OLED_W_COM(0Xa6);
		OLED_W_COM(0Xaf);

}
/******************************************************************************************************/
void OLED_DISPLAY_ON(void)								//开显示
{
	OLED_W_COM(0x8D);
	OLED_W_COM(0x14);	
  OLED_W_COM(0xAF);
}
/******************************************************************************************************/
void OLED_DISPLAY_OFF(void)						//关显示
{
	OLED_W_COM(0x8D);
	OLED_W_COM(0x10);	
  OLED_W_COM(0xAE);
}
/******************************************************************************************************/
void OLED_DISPLAY_CELL(void)							//清屏
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
			OLED_W_COM(0xb0+i);
			OLED_W_COM(0x10);
			OLED_W_COM(0x00);
		
			for(j=0;j<128;j++)
				OLED_W_DAT(0x00);
	}
}
/******************************************************************************************************/
void OLED_DISPLAY_8X16(u8 row,u8 line,u8 ass)								//显示ASCII字符
{
	u8 c=0,i,k;
	line*=8;row*=2;
	for(i=0;i<2;i++)
	{
		OLED_W_COM(0xb0+row);
		OLED_W_COM(line/16+0x10);
		OLED_W_COM(line%16);
		for(k=0;k<8;k++)
		{
			OLED_W_DAT(F8X16[(ass*16)+c-512]);
			c++;
		}
		row++;
	}
	
}
//******************************************************************************************************/
void OLED_DISPLAY_8X16_string(u8 row,u8 line,u8 *data)//显示字符串
{
	u8 k=0;
	
	while(data[k]!='\0')
	{
		OLED_DISPLAY_8X16(row,k+line-1,data[k++]);
		
	}
}
///******************************************************************************************************/
void OLED_DISPLAY_16x16(u8 row,u8 line,u8 num)								//显示汉字 横排最多8个数字，一列最多为四个汉字
{

u8 c=0,i,k;
	line*=16;row*=2;
	for(i=0;i<2;i++)
	{
		OLED_W_COM(0xb0+row);
		OLED_W_COM(line/16+0x10);
		OLED_W_COM(line%16);
		for(k=0;k<16;k++)
		{OLED_W_DAT(hanzhi[(num*32)+c]);
			c++;}row++;
	}
	

}
/******************************************************************************************************/
void OLED_DISPLAY_bmp(void)								//显示图片	
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
			OLED_W_COM(0xb0+i);
			OLED_W_COM(0x10);
			OLED_W_COM(0x02);
		
			for(j=0;j<128;j++)
				OLED_W_DAT(BMP[j+i*128]);
	}
}
/******************************************************************************************************/
void OLED_DISPLAT_Number(u8 x,u16 number)						//显示数字
{
	u8 data[7],y=0;
	u16 j=10000;
	while(j)
	{
		data[y++]=number/j+48;
		number%=j;
		j/=10;	
		
	}
data[y]='\0';
OLED_DISPLAY_8X16_string(x,0,data);


}
void OLED_DISPLAT_HEX(u8 x,u32 data)						//显示十六进制数最多显示8位
{
	
	u8 y,tmp,data_display[9];
	u32 data2=data;
	for(y=0;y<8;y++)
	{
				tmp=data2&0xf;
				if(tmp<10)
				{
					data_display[7-y]=tmp+'0';
					
				}else
				{
					data_display[7-y]=tmp+'A'-10;
				}
				data2>>=4;
	}
	data_display[8]='\0';
	
	OLED_DISPLAY_8X16_string(x,6,data_display);
	

}

/******************************************************************************************************/
void OLED_CTS_DISPLAY(u16 temp, u8 rh)//恒温系统  温度与继电器状态
{
	u8 data[6],data2[6];
	data[0]=temp/1000+48;
	data[1]=temp/100%10+48;
	data[2]='.';
	data[3]=temp%10+48;
	data[4]=temp%100/10+48;
	data[5]='\0';
	data2[0]=rh/10+48;
	data2[1]=rh%10+48;
	data2[2]='.';
	data2[3]=0+48;
	data2[4]=0+48;
	data2[5]='\0';
	//将输入的温度数值转化成字符便于显示
	OLED_DISPLAY_16x16(0,2,5);
	OLED_DISPLAY_16x16(0,3,6);
	OLED_DISPLAY_16x16(0,4,2);
	OLED_DISPLAY_16x16(0,5,3); 
	OLED_DISPLAY_8X16_string(2,0," tp:");
	OLED_DISPLAY_8X16_string(3,0," rh:");
	OLED_DISPLAY_8X16_string(2,5,data);
	OLED_DISPLAY_8X16_string(3,5,data2);
	OLED_DISPLAY_16x16(2,5,4);
	OLED_DISPLAY_8X16(2,12,'C');
	OLED_DISPLAY_8X16(3,12,'%');
	
	

}

void OLED_DISPLAY_SYSTEM(void)
{


	OLED_DISPLAY_16x16(0,2,5);
	OLED_DISPLAY_16x16(0,3,6);
	OLED_DISPLAY_16x16(0,4,2);
	OLED_DISPLAY_16x16(0,5,3); 

}

