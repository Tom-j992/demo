#include "led.h"
void LED_Init(void)//��ʼ������
{
	GPIO_InitTypeDef GPIO_Initstr;
	//�����ʼ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//��PCʱ��

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstr);
	//����PC13��14��15Ϊ����������ٶ�50mhz
	

	GPIO_SetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	//����ߣ�ledΪ�͵�ƽ��Ч������Ĭ�ϳ�ʼ������Ϊ��
}




