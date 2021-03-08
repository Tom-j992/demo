#include "relay.h"
void RELAY_Init(void)//初始函数
{
	GPIO_InitTypeDef GPIO_Initstr;
	//定义初始化变量	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//打开PB时钟

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_13;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//设置PB13为推挽输出，速度50mhz
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	//继电器低电平有效初始化需要拉高
}

