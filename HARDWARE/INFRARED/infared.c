#include "infared.h"

void INFARED_Init(void)//��ʼ������
{
	GPIO_InitTypeDef GPIO_Initstr; 
	//�����ʼ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//��PAʱ��

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//����PB12Ϊ���������͸���
}

