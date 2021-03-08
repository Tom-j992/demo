#include "beep.h"
#include "delay.h"
#include "usart3.h"

void BEEP_Init(void)//��ʼ������
{
	GPIO_InitTypeDef GPIO_Initstr;
	//�����ʼ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//��PAʱ��

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_8;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstr);
	//����PA8Ϊ�������
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	//�����
}

void BEEP_1(u8 fq)
{ //��������һ��
	u16 i,j=fq;
	while(j--)
		{
			for(i=0;i<200;i++){
			beep=0; //�������ӿ����0
			delay_us(500); //��ʱ		
			beep=1; //�������ӿ�����ߵ�ƽ1
			delay_us(500); //��ʱ		
			}
		}
}
uc16 music1[]={ //����1�����ݱ�������������ż���ǳ��ȣ�
	
NOTE_0,racket_1_2,	
NOTE_7,racket_1_2,
NOTE_H1,racket_1_2,
NOTE_7,racket_1_4,
NOTE_5,racket_1_4,
NOTE_3,racket_delay,
NOTE_0,racket_delay,	//����һֱ��
NOTE_0,racket_1_2,
NOTE_7,racket_1_2,
NOTE_7,racket_1_2,
NOTE_5,racket_1_4,
NOTE_3,racket_1_4,
NOTE_5,racket_1_2,
NOTE_7,racket_1_4,
NOTE_6,racket_1_4,
NOTE_6,racket_1_4,
NOTE_5,racket_3_4,//���緽ʽ����ûɾ
NOTE_0,racket_1_2,
NOTE_5,racket_1_2,
NOTE_5,racket_1_2,
NOTE_1,racket_1_4,
NOTE_1,racket_1_4,
NOTE_1,racket_delay,
NOTE_0,racket_delay,	//����ҵĺ�
NOTE_0,racket_3_4,
NOTE_5,racket_1_2,
NOTE_5,racket_1_2,
NOTE_4,racket_1_4,
NOTE_4,racket_1_4,
NOTE_4,racket_1_2,
NOTE_1,racket_1_4,
NOTE_5,racket_1_4,
NOTE_5,racket_1_2,
NOTE_4,racket_1_2,
NOTE_4,racket_3_4,//��ȴ���ֻٵ�
NOTE_7,racket_1_4,
NOTE_H1,racket_1_2,
NOTE_7,racket_1_4,
NOTE_5,racket_1_4,
NOTE_3,racket_delay,
NOTE_0,racket_delay,//Ҳ����һ����
NOTE_0,racket_3_4,
NOTE_H2,racket_1_4,
NOTE_H2,racket_1_2,
NOTE_7,racket_1_4,
NOTE_5,racket_1_4,
NOTE_7,racket_1_2,
NOTE_H2,racket_1_4,
NOTE_7,racket_1_4,
NOTE_7,racket_1_2,
NOTE_5,racket_1_2,
NOTE_5,racket_3_4,//�и��ط�˯���Է�
NOTE_H3,racket_1_4,
NOTE_H3,racket_1_2,
NOTE_H2,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_6,racket_delay,
NOTE_H3,racket_1_2,
NOTE_H2,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_6,racket_1_2,
NOTE_5,racket_1_2,
NOTE_6,racket_delay,
NOTE_6_1,racket_delay,
NOTE_5,racket_1_2,
NOTE_6,racket_1_4,
NOTE_7,racket_1_4,
NOTE_7,racket_1_4,
NOTE_H3,racket_3_4,//����ôȥ����ҹ�ߵ���ͷ��Ҳ�ղ���
NOTE_H1,racket_delay,
NOTE_H1,racket_delay,
NOTE_H1,racket_1_2,
NOTE_6,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_H2,racket_1_2,
NOTE_7,racket_1_4,
NOTE_7,racket_1_2,
NOTE_5,racket_1_4,
NOTE_5,racket_1_4,
NOTE_5,racket_1_2,
NOTE_3,racket_1_4,
NOTE_6,racket_1_4,
NOTE_6,racket_1_4,
NOTE_7,racket_3_4,//0
NOTE_7,racket_1_2,
NOTE_6,racket_1_4,
NOTE_H3,racket_1_4,
NOTE_H2,racket_1_2,
NOTE_H1,racket_1_4,
NOTE_6,racket_1_4,//0
NOTE_6,racket_3_4,
NOTE_5,racket_1_4,
NOTE_H1,racket_1_2,
NOTE_6,racket_1_4,
NOTE_6,racket_1_4,//0
NOTE_6,racket_1_4,
NOTE_5,racket_1_2,
NOTE_5,racket_1_4,
NOTE_H2,racket_1_2,
NOTE_H1,racket_1_4,
NOTE_H2,racket_1_4,//0
NOTE_H2,racket_1_4,
NOTE_H4,racket_1_4,
NOTE_H3,racket_1_4,//0
NOTE_H3,racket_delay,
NOTE_H1,racket_1_2,
NOTE_H2,racket_1_2,
NOTE_H1,racket_delay,
NOTE_6,racket_3_4,
NOTE_6,racket_1_4,
NOTE_H1,racket_1_2,
NOTE_6,racket_1_4,
NOTE_H1,racket_1_4,//0
NOTE_H1,racket_1_4,
NOTE_H2,racket_1_2,
NOTE_7,racket_1_4,//O
NOTE_7,racket_1_2,
NOTE_5,racket_1_4,
NOTE_5,racket_1_4,//0
NOTE_5,racket_1_2,
NOTE_3,racket_1_4,
NOTE_6,racket_1_4,//0
NOTE_6,racket_1_2,
NOTE_7,racket_1_2,//0
NOTE_7,racket_1_2,
NOTE_6,racket_1_4,
NOTE_H2,racket_1_4,
NOTE_H1,racket_1_2,
NOTE_6,racket_1_4,
NOTE_6,racket_1_4,//0
NOTE_6,racket_3_4,
NOTE_H1,racket_1_4,
NOTE_H1,racket_1_2,
NOTE_6,racket_1_4,
NOTE_6,racket_1_4,//0
NOTE_6,racket_1_4,
NOTE_H5,racket_1_2,//0
NOTE_H3,racket_1_4,//0
NOTE_H3,racket_1_4,//0
NOTE_H2,racket_3_4,//0
NOTE_H2,racket_delay,
NOTE_0,racket_delay,
NOTE_5,racket_1_4,
NOTE_6,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_H2,racket_1_4,
NOTE_H2,racket_1_4,
NOTE_H2,racket_1_4,
NOTE_H2,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_H2,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_H3,racket_1_4,//0
NOTE_H3,racket_3_4,
NOTE_7,racket_1_4,//0
NOTE_7,racket_1_4,
NOTE_7,racket_1_4,
NOTE_7,racket_1_4,
NOTE_7,racket_1_4,
NOTE_7,racket_1_2,
NOTE_6,racket_1_4,
NOTE_H1,racket_1_4,//0
NOTE_H1,racket_1_2,
NOTE_H1,racket_1_2,
NOTE_7,racket_1_2,
NOTE_5,racket_1_2,
NOTE_4,racket_delay,
NOTE_0,racket_delay,
NOTE_0,racket_1_2,
NOTE_H3,racket_1_2,
NOTE_H2,racket_1_2,
NOTE_6,racket_1_2,
NOTE_H3,racket_1_2,
NOTE_H2,racket_1_4,
NOTE_6,racket_1_4,//0
NOTE_6,racket_1_4,
NOTE_H3,racket_1_2,//0
NOTE_H2,racket_1_4,
NOTE_H2,racket_delay,
NOTE_5,racket_1_4,
NOTE_6,racket_1_4,
NOTE_H1,racket_1_4,
NOTE_H2,racket_1_4,//0
NOTE_H2,racket_1_2,
NOTE_H2,racket_1_2,
NOTE_H2,racket_1_2,
NOTE_H1,racket_1_2,
NOTE_H2,racket_1_4,
NOTE_H1,racket_1_2,
NOTE_H3,racket_1_4,//0
NOTE_H3,racket_3_4,
NOTE_H5,racket_1_4,
NOTE_H5,racket_1_2,
NOTE_H4,racket_1_4,
NOTE_H4,racket_1_4,//0
NOTE_H4,racket_1_2,
NOTE_H1,racket_1_4,
NOTE_H5,racket_1_4,//0
NOTE_H5,racket_1_2,
NOTE_H4,racket_1_2,
NOTE_H1,racket_1_4,
NOTE_H2,racket_3_4,
NOTE_H3,racket_1_2,
NOTE_H5,racket_1_4,
NOTE_H5,racket_1_4,//0
NOTE_H5,racket_1_4,
NOTE_H5,racket_1_2,
NOTE_H2,racket_1_2,
NOTE_H3,racket_1_4,
NOTE_H3,racket_1_4,//0
NOTE_H3,racket_1_2,
NOTE_5,racket_1_2,
NOTE_4,racket_delay,
NOTE_H3,racket_delay,
NOTE_H2,racket_delay,
NOTE_H2,racket_1_2,//0
NOTE_H1,racket_1_2,
NOTE_H1,racket_delay,
NOTE_0,racket_delay,
NOTE_0,racket_delay,
NOTE_0,racket_delay,
NOTE_H3,racket_1_2,
NOTE_H5,racket_1_4,
NOTE_H5,racket_1_4,//0
NOTE_H5,racket_3_4,
NOTE_H5,racket_1_4,
NOTE_H2,racket_1_2,
NOTE_H3,racket_1_4,
NOTE_H3,racket_1_4,//0
NOTE_H3,racket_1_2,
NOTE_5,racket_1_2,
NOTE_4,racket_delay,
NOTE_H3,racket_delay,
NOTE_H2_2,racket_delay,
NOTE_6,racket_delay,
NOTE_H1,racket_delay,
NOTE_0,racket_delay,
NOTE_0,racket_delay,
NOTE_0,racket_delay,
};

u8 delay_mode[]={//�����������
1,1,1,1,1,1,1,1,1,1,
1,1,1,1,0,1,1,1,1,1,
1,0,1,0,1,1,1,1,1,0,
0,0,0,0,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,0,1,
0,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,0,1,1,1,
1,1,1,0,1,1,0,1,1,0,
1,1,0,1,0,1,1,1,1,1,
0,1,1,1,1,0,1,1,1,1,
	
1,0,1,1,0,1,1,1,1,1,
1,1,1,0,1,1,0,1,1,0,
1,1,0,1,0,1,1,1,1,1,
0,1,1,1,1,0,1,0,0,0,
0,1,1,1,1,1,1,1,1,1,
1,1,1,0,1,0,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,
1,1,1,1,1,0,1,0,1,1,
1,1,1,0,1,1,1,1,1,1,
0,1,1,1,1,0,1,1,0,1,

1,1,1,1,1,0,1,1,1,1,
0,1,1,1,1,1,0,1,1,1,
1,1,1,1,0,1,1,1,1,0,

};
void MIDI_PLAY(void)
{ //MIDI����
	u16 i,e;
	for(i=0;i<180;i++){
		for(e=0;e<music1[i*2]*music1[i*2+1]/1000;e++){
			beep=0;//�������ӿ����0
			delay_us(500000/music1[i*2]/10); //��ʱ		
			beep=1;//�������ӿ�����ߵ�ƽ1
			delay_us(500000/music1[i*2]/10*9); //��ʱ	
		}	
		if(delay_mode[i]==1)//�ж��Ƿ���Ҫ���
		delay_us(racket_delay);
		
	}
}

/*����midi���ֶ�Ӧ��Ƶ������������*/

