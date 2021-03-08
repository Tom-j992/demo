#include "dht11.h"
#include "delay.h"
#include "oled.h"
volatile u8 RX_DHT11[5];//�����¶ȴ�������������



void DHT11_Init(u8 mode)//��ʼ������
{
	GPIO_InitTypeDef GPIO_Initstr;
	//�����ʼ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//��PBʱ��
	
	if(mode==OUT)			//���
		{
			GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
			GPIO_Initstr.GPIO_Pin=GPIO_Pin_11;
			GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_Init(GPIOA,&GPIO_Initstr);
			GPIO_SetBits(GPIOA,GPIO_Pin_11);
		}
	else if(mode==IN)	//����
		{
			GPIO_Initstr.GPIO_Mode=GPIO_Mode_IN_FLOATING;
			GPIO_Initstr.GPIO_Pin=GPIO_Pin_11;
			GPIO_Init(GPIOA,&GPIO_Initstr);
		}
		
		
		//���ڵ��������Լ�Ҫ����ҲҪ���
}

u8 DHT11_R_data(void)
{
	
	u8 cnt=0,i,j;
	//���������������cnt,ѭ������i j
	for(i=0;i<5;i++)
				RX_DHT11[i]=0;		//�����������
	delay_ms(50);						//�ȴ�50ms
	DHT11_Init(OUT);				//���ö˿�״̬Ϊ���
	DHT11_OUT_DATA=0;
	delay_ms(18);						//����18ms
	DHT11_OUT_DATA=1;
	delay_us(40);						//����40us
	DHT11_OUT_DATA=1;				//����������
	DHT11_Init(IN);					//���ö˿�״̬Ϊ���룬׼����������
	if(DHT11_IN_DATA==0)		//�ж��Ƿ�õ��¶ȴ�������Ӧ
	{
			while(!DHT11_IN_DATA&&cnt<100) 
			{
				cnt++;
				delay_us(1);
			}//�ȴ��͵�ƽ����
			if(cnt>100)return 0;//��ʱ�˳�
				cnt=0;
				while(DHT11_IN_DATA&&cnt<100)
			{
				cnt++;
				delay_us(1);
			}//�ȴ��ߵ�ƽ����
			if(cnt>100)return 0;//��ʱ�˳�
			cnt=0;
			//�ȴ���ƽ����
				for(i=0;i<5;i++)
				{
						for(j=0;j<8;j++)
						{
							
								
								while(DHT11_IN_DATA&&cnt<60)
								{cnt=0;
									cnt++;
									delay_us(1);
								}	
								if(cnt>60)return 0;//��ʱ�˳�
								cnt=0;
								while(!DHT11_IN_DATA&&cnt<100)
								{
									cnt++;
									delay_us(1);
								}
								if(cnt>100)return 0;//��ʱ�˳�
								delay_us(40);				//��ʱ�ȴ�
								RX_DHT11[i]<<=1;	
									if(DHT11_IN_DATA)
									RX_DHT11[i]|=0x01;//������ݱ�������������
								
											
							}
					}
			

			if(RX_DHT11[4]!=(RX_DHT11[0]+RX_DHT11[1]+RX_DHT11[2]+RX_DHT11[3]))
			{
				for(i=0;i<5;i++)
				RX_DHT11[i]=0;
				return 0;		 //У��ʧ��������ݷ���0
			}else return 4;//У��ɹ�������ȷ����4  0100
			
	
		}else return 0;//û�л�Ӧ����0��˵��û�м�⵽�¶ȴ�����
}

