#ifndef __NEC_H
#define __NEC_H
#include "delay.h"
#include "sys.h"
#define	 delay8_77us()	delay_us(8)							//��ʱ�ߵ�ƽʱ��
#define	 delay17_53us()	delay_us(17)						//��ʱ�͵�ƽʱ��
#define  NEC_TX   		 PAout(2)
#define  NEC_RX   		 PAin(3)

extern u32 Each_bit_duration[120];		// ��¼ÿһλ���ݵ�ʱ��
extern uint8_t  Current_bit_CNT;					// ��ǰ������յ�λ��
extern uint8_t  Nec_Flag;  							//��������־λ
extern uint8_t  Mec_Code[4];					//�����뱣��ص�
void NEC_OUT_Init(void);//���ⷢ�ͳ�ʼ������
void NEC_IN_Init(void);	//���������ʼ������
void NEC_IE_code_message(u16 user_code_16bit, u8 data_code_8bit);//���ͱ�׼�ĺ���NEC
void NEC_IE_code_message_Meidi(u8 A,u8 B ,u8 C);//��������R05D����ź�
void NEC_Decoding(void);	//���������


/*��������ʽ

	��ͨ����ʼ��+��ַ��16λ+8λ������+8λ���ݷ���+������		һ�㷢��һ��
	���Ŀյ�����ʼ��+������A+����A����+������B+����B����+������C+����C����+������ ������Aͨ��Ϊ0xb2 ABC��Ϊ8λͨ����������
	
		NEC_IE_code_message_Meidi(0Xb2,0X1f,0xd8);����
		NEC_IE_code_message_Meidi(0Xb2,0X7b,0xe0);�ػ�

*/








#endif
