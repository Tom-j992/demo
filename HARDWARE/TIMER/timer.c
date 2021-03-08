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
// ��ʼ��TIM2��
// ����"timer.h"�ļ��еĺ궨�壬����TIM2�����ʱ��
//--------------------------------------------------------------------------------------------------------------
void TIM2_Time_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,(FunctionalState)ENABLE); 		// ʹ��TIM2��ʱ��
	
	//��ʱ��TIM2��ʼ��
	TIM_TimeBaseStructure.TIM_Period = TIM2_Reload_Num ; 		// ������һ�������¼���װ���Զ���װ�ؼĴ�����ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = TIM2_Frequency_Divide;// ����TIM2ʱ��Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	// ����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			// ���ݲ�����ʼ��TIM2�ļ�����ʽ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,(FunctionalState)ENABLE); 					// ����TIM2�����ж�

	
	//TIM2���ж�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  			// TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  	// ��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  		// �����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd =(FunctionalState)ENABLE; 			// ʹ��TIM2_IRQnͨ��
	NVIC_Init(&NVIC_InitStructure);  							// ��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM2, (FunctionalState)ENABLE);  									// ʹ��TIM2
}
//--------------------------------------------------------------------------------------------------------------
void TIM2_IRQHandler(void)   									//TIM2�ж�
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  		//�ж��Ƿ�ΪTIM2�ĸ����ж�
	{
			
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update );  			//���TIM2�����жϱ�־ 
		cnt++;
		dht11_cnt+=2;
		// �����յ�һ���½��غ���һ���½�������20ms�ڱ����յ�������˴κ��������Ϊ�ǳ����
		//-----------------------------------------------------------------------------
		if(Current_bit_CNT<20)//��׼��necЭ������λ����32λС���������ʱ��Ϊ���ݽ��ղ�����
		{
			Current_bit_CNT = 0;	// ����ǰ������յ�λ����0
		}
		
		
		
	}
}

