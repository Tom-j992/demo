#include "rgbled.h"
void RGBLED_Init(void)//��ʼ������
{
	GPIO_InitTypeDef GPIO_Initstr;
	//�����ʼ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//��PBʱ��

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//����PA13,14,15Ϊ�������
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	//����ͣ�����ȫ��������ǹ���������һ��ʼ��������led����
}

void LED_Color(u8 color)
{
	R_LED = 0;G_LED = 0;B_LED = 0;//�ر�led
	switch(color)									//ѡ����ɫ
	{
		case RED:R_LED = 1;break;		//���
		case BLUE:B_LED = 1;break;	//����
		case GREEN:G_LED = 1;break; //�̵�
		case WHITE:R_LED = 1;G_LED = 1;B_LED = 1;break;//��ɫ
		case BLACK:R_LED = 0;G_LED = 0;B_LED = 0;break;//���
	}

}
