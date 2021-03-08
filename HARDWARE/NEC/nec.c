#include "nec.h"
#include "delay.h"
#include "oled.h"
#include "led.h"
// �������������ݵ�ȫ�ֱ���
//------------------------------------------------------------
u32 Each_bit_duration[120];		// ��¼ÿһλ���ݵ�ʱ��
u8  Current_bit_CNT=0;				// ��ǰ������յ�λ��
u8  Nec_Flag=0;  							//��������־λ
u8  Mec_Code[4];					//�����뱣��ص�

void NEC_OUT_Init(void)//��ʼ���������ⷢ��
{
	GPIO_InitTypeDef GPIO_InitStruct;                       // ����һ��GPIO_InitTypeDef���͵ı���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // ����GPIOAʱ��
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;                  // GPIO_Pin_2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;           // ͨ���������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;          // 50MHz�ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);                      //PA2����
}



void NEC_Tx_Zero(void) //����0����    
{
	u8 i;
	
	// �ز�����0.56ms �� 26.3us * 21
	//-------------------------------
	for(i=0;i<22;i++)
	{
        //26.3us���ز��������ڣ�
		//------------------------------------
		NEC_TX=1;	// IȨ�ߣ���������
		delay8_77us();  // ��ʱ8.77us                        
											
		NEC_TX=0;	// IE���ͣ�����������
		delay17_53us(); // ��ʱ17.53us
		//------------------------------------
	}

	// �ز�������0.56ms �� 26.3us * 21
	//-------------------------------
	for(i=0;i<21;i++)
	{
        //26.3us���ز����������ڣ�
		//------------------------------------
		NEC_TX=0;	// IE���ͣ�����������
		delay8_77us();  // ��ʱ8.77us
                                            
		NEC_TX=0;	// IE���ͣ�����������
		delay17_53us(); // ��ʱ17.53us
		//------------------------------------
	}
}
// NECЭ������"1" = �ز�����0.56ms + �ز�������1.68ms
//-------------------------------------------------
void NEC_Tx_One(void)						
{
	u8 i;
	
	// �ز�����0.56ms �� 26.3us * 21
	//-------------------------------
	for(i=0;i<22;i++)
	{
		//26.3us���ز��������ڣ�
		//------------------------------------
		NEC_TX=1;    // IȨ�ߣ���������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;  // IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
		//------------------------------------
	}
	
	// �ز�������1.68ms �� 26.3us * 64
	//--------------------------------
	for(i=0;i<64;i++)
	{
		//26.3us���ز����������ڣ�
		//------------------------------------
		NEC_TX=0;	// IE���ͣ�����������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
		//------------------------------------
	}
}

// NECЭ������"1" = �ز�����4.4ms + �ز�������4.4ms
//-------------------------------------------------
void NEC_LEAR_Meidi(void){		//���ĵ�ؿ�ʼ�ź�

	u8 i;
	for(i=0;i<172;i++) 
	{
		NEC_TX=1;	// IȨ�ߣ���������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
	
	// �ز������� 4.5ms �� 26.3us * 171
	for(i=0;i<172;i++)
	{
		NEC_TX=0;	// IE���ͣ�����������
		delay8_77us();	// ��ʱ8.77us
		NEC_TX=0;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
}



// ��һ֡���ݵ���ΪNECЭ��涨�ĺ����ز������ȥ
// һ֡���ݸ�ʽ����λ��ǰ���ɵ͵��߷���8λ����
// ��֡���ݿ����ǣ���16λ�û�����ֽ�(8λ) / ��16λ�û�����ֽ�(8λ) / ��8λ������ / ��8λ������ķ���
//----------------------------------------------------------------------------------------------
void NEC_IE_One_Data(u8 Tx_One_Data)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		if( Tx_One_Data & 0x01 )
			NEC_Tx_One();
		else
			NEC_Tx_Zero();
			
		Tx_One_Data>>=1;
	}
}
// ��һ֡���ݵ���ΪNECЭ��涨�ĺ����ز������ȥ
// һ֡���ݸ�ʽ����λλ��ǰ���ɸߵ��ͷ���8λ����
// ��֡���ݿ����ǣ�/ ��8λʶ����A / ��8λ������B / ��������C �������ĵ��
void NEC_IE_One_Data_Meidi(u8 Tx_One_Data)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if( Tx_One_Data & 0x80 )
			NEC_Tx_One();
		else
			NEC_Tx_Zero();
			
		Tx_One_Data<<=1;
	}
}


// ����NEC�����ʽ����Ϣ����׼��
//----------------------------------------------------------------------------------------------------------------------
// NEC �����ʽ�� �������� + ��16λ�û�����ֽ�(8λ) + ��16λ�û�����ֽ�(8λ) + ��8λ������ + ��8λ������ķ��� + �޽����롮0�� 
//----------------------------------------------------------------------------------------------------------------------
void NEC_IE_code_message(u16 user_code_16bit, u8 data_code_8bit)
{
	u16 i;
	
	
	u8 T_user_code_high = 0xff&user_code_16bit>>8;
	
	u8 T_user_code_low = 0xff&user_code_16bit;

	// �������룺�ز�����9ms��������4.5ms
	//------------------------------------------------------------
	// �ز����� 9ms �� 26.3us * 342
	for(i=0;i<342;i++) 
	{
		NEC_TX=1;	// IȨ�ߣ���������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
	
	// �ز������� 4.5ms �� 26.3us * 171
	for(i=0;i<171;i++)
	{
	NEC_TX=0;	// IE���ͣ�����������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
	//------------------------------------------------------------
	
	
	//------------------------------------------------------------
	// ��16λ�û�����ֽ�	��8λ����
	NEC_IE_One_Data(T_user_code_low);
	
	// ��16λ�û�����ֽڣ�8λ����
	NEC_IE_One_Data(T_user_code_high);
	
	// ��8λ������ ��8λ����
	NEC_IE_One_Data(data_code_8bit);
	
	// ��8λ������ķ��룺8λ����
	NEC_IE_One_Data(~data_code_8bit);
	
	//------------------------------------------------------------
	
	// �޽����롮0��
	//--------------
	NEC_Tx_Zero();
	//--------------
}



// ����NEC�����ʽ����Ϣ����׼��
//---------------------------------------------------------------------------------------------------------------------------------------------------------
// NEC �����ʽ�� �������� + ��8λ��ַ�� + ��8λ��ַ���� (8λ) + ��8λ������B + ��8λ������B�ķ���+��8λ������C + ��8λ������C�ķ��� + �������� 
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void NEC_IE_code_message_Meidi(u8 A,u8 B ,u8 C)
{
		u16 i;
		u8 data[7];
			data[0]=A;data[1]=~A;
			data[2]=B;data[3]=~B;
			data[4]=C;data[5]=~C;
		// �������룺�ز�����4.5ms��������4.5ms
	NEC_LEAR_Meidi();
	//------------------------------------------------------------
	//send A ~A B ~B C ~C
	
		NEC_IE_One_Data_Meidi(data[0]);
		NEC_IE_One_Data_Meidi(data[1]);
		NEC_IE_One_Data_Meidi(data[2]);
		NEC_IE_One_Data_Meidi(data[3]);
		NEC_IE_One_Data_Meidi(data[4]);
		NEC_IE_One_Data_Meidi(data[5]);
	
		// �޽�����ָ���0.54ms+5.22ms
	//--------------
		for(i=0;i<22;i++) 
	{
	
		NEC_TX=1;	// IȨ�ߣ���������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
		// �ز������� 4.5ms �� 26.3us * 171
	for(i=0;i<200;i++)
	{
		NEC_TX=0;	// IE���ͣ�����������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
	//--------------
	
		// �������룺�ز�����4.5ms��������4.5ms
	NEC_LEAR_Meidi();
	//------------------------------------------------------------
	//send A ~A B ~B C ~C
	
		NEC_IE_One_Data_Meidi(data[0]);
		NEC_IE_One_Data_Meidi(data[1]);
		NEC_IE_One_Data_Meidi(data[2]);
		NEC_IE_One_Data_Meidi(data[3]);
		NEC_IE_One_Data_Meidi(data[4]);
		NEC_IE_One_Data_Meidi(data[5]);
	
		// �޽�����ָ���0.54ms+5.22ms
	//--------------
		for(i=0;i<22;i++) 
	{
	
		NEC_TX=1;	// IȨ�ߣ���������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
		// �ز������� 4.5ms �� 26.3us * 171
	for(i=0;i<200;i++)
	{
		NEC_TX=0;	// IE���ͣ�����������
		delay8_77us();	// ��ʱ8.77us
		
		NEC_TX=0;	// IE���ͣ�����������
		delay17_53us();	// ��ʱ17.53us
	}
	//--------------
}

void NEC_IN_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/* ����PC0���� */
	//---------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// ʹ��PA�˿�ʱ��											
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;	                // ��������ģʽ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;						// PA3
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	//---------------------------------------------------------------------------
	
	/* ����PC0�����ж�ģʽ */
	//----------------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			// ʹ��ӳ��ʱ��
    
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3); // ���ж���0ӳ�䵽PC0����
    
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;			// ѡ��Ϊ�ж�
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; 		// �½����ж�
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Line = EXTI_Line3;						// ѡ���ⲿ�ж���3
	EXTI_Init(&EXTI_InitStruct);								
	
	 /* ����NVIC */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;		// ��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;				// ��Ӧ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn; 				// �ж�ͨ�����ⲿ�ж���3
	NVIC_Init(&NVIC_InitStruct);
}

//-------------------------------------------------------------------------------------------------------
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) 	// �ж��Ƿ�Ϊ�ж���3���ж�
	{
		EXTI_ClearITPendingBit(EXTI_Line3);     // ����жϱ�־λ
		
		if(TIM2->CNT>900){
		Each_bit_duration[Current_bit_CNT] = TIM2->CNT;	// �����½��ص�TIM2��������Each_bit_duration[x]��
														// Each_bit_duration[0]�������
		Current_bit_CNT ++ ;	// ����ǰ������յ�λ��+1
		
		// 1��������һ���½��صļ�ʱ
		// 2���ȴ���һ���½���20ms
		//---------------------------------------------------------------------
		TIM2->CNT=0;			// ������չܽŽ��յ�һ���½��غ󣬽�TIM2��������0
			}else 
		{
			TIM2->CNT=0;			// ������չܽŽ��յ�һ���½��غ󣬽�TIM2��������0
		
		}
	} 	
}

void NEC_Decoding(void)//���������
{
	int i,j,k;
		Nec_Flag=0;
	if(Current_bit_CNT>0)
	{
		
		if(Current_bit_CNT>90)		//����Э��       ��ʼ�� +A+A��+B+B'+C+C'+Rֹͣ��
		{
				
			for(i=1;i<Current_bit_CNT-40;i++)//������ʼ��Ϊ8.8ms.�ҵ���ʼ��
		
			{
				if(Each_bit_duration[i]>7000&&Each_bit_duration[i]<9500)//�ҵ���ʼ��
				{
					Nec_Flag=0X22;
					break;
					
				}
				
			}
		
			if(Nec_Flag==0X22&&i<Current_bit_CNT-39){
				for(k=0;k<3;k++)
				{
						
						for(j=0;j<=8;j++)//A
						{
								if(Each_bit_duration[i+j]>2000&& Each_bit_duration[i+j]<2500)
								{
										
										Mec_Code[k]&=0XFE;//���
										Mec_Code[k]|=0X01;//
									if(j!=8)
										Mec_Code[k]<<=1;
								
								}
								else if(Each_bit_duration[i+j]>1000&& Each_bit_duration[i+j]<1250){
									
										Mec_Code[k]&=0XFE;//���
									if(j!=8)
										Mec_Code[k]<<=1;
										
								}
						}		
						
					
						i+=16;
									
				}
				Current_bit_CNT=0;
			
}
	
		
		}else		if(Current_bit_CNT>40)	//��׼Э����� ��ʼ��+16λ�û���+��λ������+��λ���ݷ���+������
		{
					
			for(i=1;i<Current_bit_CNT-32;i++)//������ʼ��Ϊ8.8ms.�ҵ���ʼ��
		
			{
				if(Each_bit_duration[i]>12000&&Each_bit_duration[i]<16000)//�ҵ���ʼ��
				{
					Nec_Flag=0x21;
					break;
					
				}
				
			}	
			if(Nec_Flag==0x21&&i<Current_bit_CNT-32){
				for(k=0;k<3;k++)
				{
				
						for(j=0;j<=8;j++)//A
						{
								if(Each_bit_duration[i+j]>2000&& Each_bit_duration[i+j]<2600)
								{	
										
										Mec_Code[k]&=0X7f;//���
										Mec_Code[k]|=0X80;//
									if(j!=8)
										Mec_Code[k]>>=1;			
								
								}
								else if(Each_bit_duration[i+j]>1000&& Each_bit_duration[i+j]<1250){
										
										
										Mec_Code[k]&=0X7f;//���
										if(j!=8)
										Mec_Code[k]>>=1;
								}
						}		
							i+=8;	
				}
				Current_bit_CNT=0;
	
			}
		
		}
	}else Nec_Flag=0;
	

}

//-------------------------------------------------------------------------------------------------------
