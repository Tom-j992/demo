#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"
#define DHT11_OUT_DATA  PAout(11)
#define DHT11_IN_DATA  PAin(11)
#define OUT 1
#define IN  2
extern volatile u8 RX_DHT11[5];//��������
void DHT11_Init(u8 mode);			//��ʼ���¶ȴ�����
u8 DHT11_R_data(void);				//��ȡ����
	

#endif

