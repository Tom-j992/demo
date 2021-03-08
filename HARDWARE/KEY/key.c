#include "key.h"
#include "delay.h"
void KEY_Init(void)//初始化函数
{
	GPIO_InitTypeDef GPIO_Initstr;
	//定义初始化变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//打开PB时钟
	
	GPIO_Initstr.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//设置PB0为上拉输入
  
  GPIO_Initstr.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//设置PB1为上拉输入
 
}

//
//读取按键值并返回
//
u8 KEY_Scanf(void)
{
  u8 key=0;
  
  if(KEY_1==0||KEY_2==0)			//判断是否有按键按下
  {
    delay_ms(20);							//延时消抖
    if(KEY_1==0||KEY_2==0)		//判断是否有按键按下
      {
          if(KEY_1==0)				//按键1按下
            key=1;
          else if(KEY_2==0)		//按键2按下
            key=2;
          else
            key=0;						//没有按键按下

        while(!(KEY_1&KEY_2));//松手检测
      }
        
  }
  return key;									//返回按键值
  
}








