#include "rgbled.h"
void RGBLED_Init(void)//初始化函数
{
	GPIO_InitTypeDef GPIO_Initstr;
	//定义初始化变量
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//打开PB时钟

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//设置PA13,14,15为推挽输出
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	//输出低，由于全彩数码管是共阴，所以一开始先拉低让led先灭
}

void LED_Color(u8 color)
{
	R_LED = 0;G_LED = 0;B_LED = 0;//关闭led
	switch(color)									//选择颜色
	{
		case RED:R_LED = 1;break;		//红灯
		case BLUE:B_LED = 1;break;	//蓝灯
		case GREEN:G_LED = 1;break; //绿灯
		case WHITE:R_LED = 1;G_LED = 1;B_LED = 1;break;//白色
		case BLACK:R_LED = 0;G_LED = 0;B_LED = 0;break;//灭掉
	}

}
