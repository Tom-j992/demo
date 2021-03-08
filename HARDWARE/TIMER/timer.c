#include "timer.h"
#include "led.h"
#include "nec.h"
#include "oled.h"
#include "usart3.h"
#include "wifi.h"
#include "beep.h"
#include "sys.h"
 u8 cnt=0;
 u8 dht11_cnt=0;
// 初始化TIM2：
// 根据"timer.h"文件中的宏定义，设置TIM2的溢出时间
//--------------------------------------------------------------------------------------------------------------
void TIM2_Time_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,(FunctionalState)ENABLE); 		// 使能TIM2的时钟
	
	//定时器TIM2初始化
	TIM_TimeBaseStructure.TIM_Period = TIM2_Reload_Num ; 		// 设置下一个更新事件后，装入自动重装载寄存器的值	
	TIM_TimeBaseStructure.TIM_Prescaler = TIM2_Frequency_Divide;// 设置TIM2时钟预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			// 根据参数初始化TIM2的计数方式
 
	TIM_ITConfig(TIM2,TIM_IT_Update,(FunctionalState)ENABLE); 					// 允许TIM2更新中断

	
	//TIM2的中断NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  			// TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  	// 抢占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  		// 子优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd =(FunctionalState)ENABLE; 			// 使能TIM2_IRQn通道
	NVIC_Init(&NVIC_InitStructure);  							// 初始化NVIC寄存器


	TIM_Cmd(TIM2, (FunctionalState)ENABLE);  									// 使能TIM2
}
//--------------------------------------------------------------------------------------------------------------
void TIM2_IRQHandler(void)   									//TIM2中断
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  		//判断是否为TIM2的更新中断
	{
			
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update );  			//清除TIM2更新中断标志 
		cnt++;
		dht11_cnt+=2;
		// 当接收到一个下降沿后，下一个下降沿须在20ms内被接收到，否则此次红外接收认为是出错的
		//-----------------------------------------------------------------------------
		if(Current_bit_CNT<20)//标准的nec协议数据位都有32位小于这个数此时认为数据接收不完整
		{
			Current_bit_CNT = 0;	// 将当前红外接收的位数清0
		}
		
		
		
	}
}

