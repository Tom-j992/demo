#include "beep.h"
#include "delay.h"
#include "usart3.h"

void BEEP_Init(void)//初始化函数
{
	GPIO_InitTypeDef GPIO_Initstr;
	//定义初始化变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//打开PA时钟

	GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_8;
	GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstr);
	//设置PA8为推挽输出
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	//输出高
}

void BEEP_1(u8 fq)
{ //蜂鸣器响一声
	u16 i,j=fq;
	while(j--)
		{
			for(i=0;i<200;i++){
			beep=0; //蜂鸣器接口输出0
			delay_us(500); //延时		
			beep=1; //蜂鸣器接口输出高电平1
			delay_us(500); //延时		
			}
		}
}
uc16 music1[]={ //音乐1的数据表（奇数是音调，偶数是长度）
	
NOTE_0,racket_1_2,	
NOTE_7,racket_1_2,
NOTE_H1,racket_1_2,
NOTE_7,racket_1_4,
NOTE_5,racket_1_4,
NOTE_3,racket_delay,
NOTE_0,racket_delay,	//电视一直闪
NOTE_0,racket_1_2,
NOTE_7,racket_1_2,
NOTE_7,racket_1_2,
NOTE_5,racket_1_4,
NOTE_3,racket_1_4,
NOTE_5,racket_1_2,
NOTE_7,racket_1_4,
NOTE_6,racket_1_4,
NOTE_6,racket_1_4,
NOTE_5,racket_3_4,//联络方式都还没删
NOTE_0,racket_1_2,
NOTE_5,racket_1_2,
NOTE_5,racket_1_2,
NOTE_1,racket_1_4,
NOTE_1,racket_1_4,
NOTE_1,racket_delay,
NOTE_0,racket_delay,	//你待我的好
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
NOTE_4,racket_3_4,//我却错手毁掉
NOTE_7,racket_1_4,
NOTE_H1,racket_1_2,
NOTE_7,racket_1_4,
NOTE_5,racket_1_4,
NOTE_3,racket_delay,
NOTE_0,racket_delay,//也曾想一起想
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
NOTE_5,racket_3_4,//有个地方睡觉吃饭
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
NOTE_H3,racket_3_4,//可怎么去熬日夜颠倒连头款也凑不到
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

u8 delay_mode[]={//间隔或者连续
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
{ //MIDI音乐
	u16 i,e;
	for(i=0;i<180;i++){
		for(e=0;e<music1[i*2]*music1[i*2+1]/1000;e++){
			beep=0;//蜂鸣器接口输出0
			delay_us(500000/music1[i*2]/10); //延时		
			beep=1;//蜂鸣器接口输出高电平1
			delay_us(500000/music1[i*2]/10*9); //延时	
		}	
		if(delay_mode[i]==1)//判断是否需要间隔
		delay_us(racket_delay);
		
	}
}

/*根据midi音乐对应的频率来播放音乐*/

