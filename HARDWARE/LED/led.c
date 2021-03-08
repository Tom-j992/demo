#include "led.h"
void LED_Init(void)//初始化函数
{
	GPIO_InitTypeDef GPIO_Initstr;
	//定义初始化变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//打开PC时钟

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstr);
	//设置PC13，14，15为推挽输出，速度50mhz
	

	GPIO_SetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	//输出高，led为低电平有效，所以默认初始化过后为灭
}




