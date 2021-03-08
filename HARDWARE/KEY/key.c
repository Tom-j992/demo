#include "key.h"
#include "delay.h"
void KEY_Init(void)//��ʼ������
{
	GPIO_InitTypeDef GPIO_Initstr;
	//�����ʼ������
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//��PBʱ��
	
	GPIO_Initstr.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//����PB0Ϊ��������
  
  GPIO_Initstr.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstr.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO_Initstr);
	//����PB1Ϊ��������
 
}

//
//��ȡ����ֵ������
//
u8 KEY_Scanf(void)
{
  u8 key=0;
  
  if(KEY_1==0||KEY_2==0)			//�ж��Ƿ��а�������
  {
    delay_ms(20);							//��ʱ����
    if(KEY_1==0||KEY_2==0)		//�ж��Ƿ��а�������
      {
          if(KEY_1==0)				//����1����
            key=1;
          else if(KEY_2==0)		//����2����
            key=2;
          else
            key=0;						//û�а�������

        while(!(KEY_1&KEY_2));//���ּ��
      }
        
  }
  return key;									//���ذ���ֵ
  
}








