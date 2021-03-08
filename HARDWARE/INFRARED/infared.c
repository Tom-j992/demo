#include "infared.h"

void INFARED_Init(void)//初始化函数
{
	GPIO_InitTypeDef GPIO_Initstr; 
	//定义初始化变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//打开PA时钟

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//设置PB12为下拉，降低干扰
}

