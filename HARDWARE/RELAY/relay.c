#include "relay.h"
void RELAY_Init(void)//��ʼ����
{
	GPIO_InitTypeDef GPIO_Initstr;
	//�����ʼ������	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//��PBʱ��

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_13;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//����PB13Ϊ����������ٶ�50mhz
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	//�̵����͵�ƽ��Ч��ʼ����Ҫ����
}

