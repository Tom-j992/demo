#include "dht11.h"
#include "delay.h"
#include "oled.h"
volatile u8 RX_DHT11[5];//接收温度传感器数据数组



void DHT11_Init(u8 mode)//初始化函数
{
	GPIO_InitTypeDef GPIO_Initstr;
	//定义初始化变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//打开PB时钟
	
	if(mode==OUT)			//输出
		{
			GPIO_Initstr.GPIO_Mode=GPIO_Mode_Out_PP;
			GPIO_Initstr.GPIO_Pin=GPIO_Pin_11;
			GPIO_Initstr.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_Init(GPIOA,&GPIO_Initstr);
			GPIO_SetBits(GPIOA,GPIO_Pin_11);
		}
	else if(mode==IN)	//输入
		{
			GPIO_Initstr.GPIO_Mode=GPIO_Mode_IN_FLOATING;
			GPIO_Initstr.GPIO_Pin=GPIO_Pin_11;
			GPIO_Init(GPIOA,&GPIO_Initstr);
		}
		
		
		//由于单总线所以既要输入也要输出
}

u8 DHT11_R_data(void)
{
	
	u8 cnt=0,i,j;
	//定义变量，计数器cnt,循环变量i j
	for(i=0;i<5;i++)
				RX_DHT11[i]=0;		//清除数组数据
	delay_ms(50);						//等待50ms
	DHT11_Init(OUT);				//设置端口状态为输出
	DHT11_OUT_DATA=0;
	delay_ms(18);						//拉低18ms
	DHT11_OUT_DATA=1;
	delay_us(40);						//拉高40us
	DHT11_OUT_DATA=1;				//拉高数据线
	DHT11_Init(IN);					//设置端口状态为输入，准备接受数据
	if(DHT11_IN_DATA==0)		//判断是否得到温度传感器回应
	{
			while(!DHT11_IN_DATA&&cnt<100) 
			{
				cnt++;
				delay_us(1);
			}//等待低电平结束
			if(cnt>100)return 0;//超时退出
				cnt=0;
				while(DHT11_IN_DATA&&cnt<100)
			{
				cnt++;
				delay_us(1);
			}//等待高电平结束
			if(cnt>100)return 0;//超时退出
			cnt=0;
			//等待电平结束
				for(i=0;i<5;i++)
				{
						for(j=0;j<8;j++)
						{
							
								
								while(DHT11_IN_DATA&&cnt<60)
								{cnt=0;
									cnt++;
									delay_us(1);
								}	
								if(cnt>60)return 0;//超时退出
								cnt=0;
								while(!DHT11_IN_DATA&&cnt<100)
								{
									cnt++;
									delay_us(1);
								}
								if(cnt>100)return 0;//超时退出
								delay_us(40);				//延时等待
								RX_DHT11[i]<<=1;	
									if(DHT11_IN_DATA)
									RX_DHT11[i]|=0x01;//获得数据保存在数组中内
								
											
							}
					}
			

			if(RX_DHT11[4]!=(RX_DHT11[0]+RX_DHT11[1]+RX_DHT11[2]+RX_DHT11[3]))
			{
				for(i=0;i<5;i++)
				RX_DHT11[i]=0;
				return 0;		 //校验失败清楚数据返回0
			}else return 4;//校验成功数据正确返回4  0100
			
	
		}else return 0;//没有回应返回0，说明没有检测到温度传感器
}

