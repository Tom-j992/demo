#include "nec.h"
#include "delay.h"
#include "oled.h"
#include "led.h"
// 缓存红外接收数据的全局变量
//------------------------------------------------------------
u32 Each_bit_duration[120];		// 记录每一位数据的时长
u8  Current_bit_CNT=0;				// 当前红外接收的位数
u8  Nec_Flag=0;  							//红外解码标志位
u8  Mec_Code[4];					//红外码保存地点

void NEC_OUT_Init(void)//初始化函数红外发射
{
	GPIO_InitTypeDef GPIO_InitStruct;                       // 定义一个GPIO_InitTypeDef类型的变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // 允许GPIOA时钟
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;                  // GPIO_Pin_2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;           // 通用推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;          // 50MHz速度
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);                      //PA2拉低
}



void NEC_Tx_Zero(void) //发送0函数    
{
	u8 i;
	
	// 载波发射0.56ms ≈ 26.3us * 21
	//-------------------------------
	for(i=0;i<22;i++)
	{
        //26.3us（载波发射周期）
		//------------------------------------
		NEC_TX=1;	// IE抬高，发射红外光
		delay8_77us();  // 延时8.77us                        
											
		NEC_TX=0;	// IE拉低，不发射红外光
		delay17_53us(); // 延时17.53us
		//------------------------------------
	}

	// 载波不发射0.56ms ≈ 26.3us * 21
	//-------------------------------
	for(i=0;i<21;i++)
	{
        //26.3us（载波不发射周期）
		//------------------------------------
		NEC_TX=0;	// IE拉低，不发射红外光
		delay8_77us();  // 延时8.77us
                                            
		NEC_TX=0;	// IE拉低，不发射红外光
		delay17_53us(); // 延时17.53us
		//------------------------------------
	}
}
// NEC协议数据"1" = 载波发射0.56ms + 载波不发射1.68ms
//-------------------------------------------------
void NEC_Tx_One(void)						
{
	u8 i;
	
	// 载波发射0.56ms ≈ 26.3us * 21
	//-------------------------------
	for(i=0;i<22;i++)
	{
		//26.3us（载波发射周期）
		//------------------------------------
		NEC_TX=1;    // IE抬高，发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;  // IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
		//------------------------------------
	}
	
	// 载波不发射1.68ms ≈ 26.3us * 64
	//--------------------------------
	for(i=0;i<64;i++)
	{
		//26.3us（载波不发射周期）
		//------------------------------------
		NEC_TX=0;	// IE拉低，不发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
		//------------------------------------
	}
}

// NEC协议数据"1" = 载波发射4.4ms + 载波不发射4.4ms
//-------------------------------------------------
void NEC_LEAR_Meidi(void){		//美的电控开始信号

	u8 i;
	for(i=0;i<172;i++) 
	{
		NEC_TX=1;	// IE抬高，发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
	
	// 载波不发射 4.5ms ≈ 26.3us * 171
	for(i=0;i<172;i++)
	{
		NEC_TX=0;	// IE拉低，不发射红外光
		delay8_77us();	// 延时8.77us
		NEC_TX=0;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
}



// 将一帧数据调制为NEC协议规定的红外载波发射出去
// 一帧数据格式：低位在前，由低到高发送8位数据
// 这帧数据可以是：②16位用户码低字节(8位) / ③16位用户码高字节(8位) / ④8位数据码 / ⑤8位数据码的反码
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
// 将一帧数据调制为NEC协议规定的红外载波发射出去
// 一帧数据格式：高位位在前，由高到低发送8位数据
// 这帧数据可以是：/ ③8位识别码A / ④8位数据码B / ⑤数据码C 用于美的电控
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


// 发送NEC编码格式的信息（标准）
//----------------------------------------------------------------------------------------------------------------------
// NEC 编码格式： ①引导码 + ②16位用户码低字节(8位) + ③16位用户码高字节(8位) + ④8位数据码 + ⑤8位数据码的反码 + ⑥结束码‘0’ 
//----------------------------------------------------------------------------------------------------------------------
void NEC_IE_code_message(u16 user_code_16bit, u8 data_code_8bit)
{
	u16 i;
	
	
	u8 T_user_code_high = 0xff&user_code_16bit>>8;
	
	u8 T_user_code_low = 0xff&user_code_16bit;

	// ①引导码：载波发射9ms，不发射4.5ms
	//------------------------------------------------------------
	// 载波发射 9ms ≈ 26.3us * 342
	for(i=0;i<342;i++) 
	{
		NEC_TX=1;	// IE抬高，发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
	
	// 载波不发射 4.5ms ≈ 26.3us * 171
	for(i=0;i<171;i++)
	{
	NEC_TX=0;	// IE拉低，不发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
	//------------------------------------------------------------
	
	
	//------------------------------------------------------------
	// ②16位用户码低字节	：8位数据
	NEC_IE_One_Data(T_user_code_low);
	
	// ③16位用户码高字节：8位数据
	NEC_IE_One_Data(T_user_code_high);
	
	// ④8位数据码 ：8位数据
	NEC_IE_One_Data(data_code_8bit);
	
	// ⑤8位数据码的反码：8位数据
	NEC_IE_One_Data(~data_code_8bit);
	
	//------------------------------------------------------------
	
	// ⑥结束码‘0’
	//--------------
	NEC_Tx_Zero();
	//--------------
}



// 发送NEC编码格式的信息（标准）
//---------------------------------------------------------------------------------------------------------------------------------------------------------
// NEC 编码格式： ①引导码 + ②8位地址码 + ③8位地址反码 (8位) + ④8位数据码B + ⑤8位数据码B的反码+④8位数据码C + ⑤8位数据码C的反码 + ⑥连接码 
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void NEC_IE_code_message_Meidi(u8 A,u8 B ,u8 C)
{
		u16 i;
		u8 data[7];
			data[0]=A;data[1]=~A;
			data[2]=B;data[3]=~B;
			data[4]=C;data[5]=~C;
		// ①引导码：载波发射4.5ms，不发射4.5ms
	NEC_LEAR_Meidi();
	//------------------------------------------------------------
	//send A ~A B ~B C ~C
	
		NEC_IE_One_Data_Meidi(data[0]);
		NEC_IE_One_Data_Meidi(data[1]);
		NEC_IE_One_Data_Meidi(data[2]);
		NEC_IE_One_Data_Meidi(data[3]);
		NEC_IE_One_Data_Meidi(data[4]);
		NEC_IE_One_Data_Meidi(data[5]);
	
		// ⑥结束码分隔码0.54ms+5.22ms
	//--------------
		for(i=0;i<22;i++) 
	{
	
		NEC_TX=1;	// IE抬高，发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
		// 载波不发射 4.5ms ≈ 26.3us * 171
	for(i=0;i<200;i++)
	{
		NEC_TX=0;	// IE拉低，不发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
	//--------------
	
		// ①引导码：载波发射4.5ms，不发射4.5ms
	NEC_LEAR_Meidi();
	//------------------------------------------------------------
	//send A ~A B ~B C ~C
	
		NEC_IE_One_Data_Meidi(data[0]);
		NEC_IE_One_Data_Meidi(data[1]);
		NEC_IE_One_Data_Meidi(data[2]);
		NEC_IE_One_Data_Meidi(data[3]);
		NEC_IE_One_Data_Meidi(data[4]);
		NEC_IE_One_Data_Meidi(data[5]);
	
		// ⑥结束码分隔码0.54ms+5.22ms
	//--------------
		for(i=0;i<22;i++) 
	{
	
		NEC_TX=1;	// IE抬高，发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
		// 载波不发射 4.5ms ≈ 26.3us * 171
	for(i=0;i<200;i++)
	{
		NEC_TX=0;	// IE拉低，不发射红外光
		delay8_77us();	// 延时8.77us
		
		NEC_TX=0;	// IE拉低，不发射红外光
		delay17_53us();	// 延时17.53us
	}
	//--------------
}

void NEC_IN_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/* 配置PC0引脚 */
	//---------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能PA端口时钟											
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;	                // 上拉输入模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;						// PA3
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	//---------------------------------------------------------------------------
	
	/* 配置PC0引脚中断模式 */
	//----------------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			// 使能映射时钟
    
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3); // 将中断线0映射到PC0线上
    
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;			// 选择为中断
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; 		// 下降沿中断
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Line = EXTI_Line3;						// 选择外部中断线3
	EXTI_Init(&EXTI_InitStruct);								
	
	 /* 配置NVIC */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;		// 抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;				// 响应优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn; 				// 中断通道：外部中断线3
	NVIC_Init(&NVIC_InitStruct);
}

//-------------------------------------------------------------------------------------------------------
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) 	// 判断是否为中断线3的中断
	{
		EXTI_ClearITPendingBit(EXTI_Line3);     // 清除中断标志位
		
		if(TIM2->CNT>900){
		Each_bit_duration[Current_bit_CNT] = TIM2->CNT;	// 将此下降沿的TIM2计数存入Each_bit_duration[x]中
														// Each_bit_duration[0]无需关心
		Current_bit_CNT ++ ;	// 将当前红外接收的位数+1
		
		// 1、方便下一个下降沿的计时
		// 2、等待下一个下降沿20ms
		//---------------------------------------------------------------------
		TIM2->CNT=0;			// 红外接收管脚接收到一个下降沿后，将TIM2计数器清0
			}else 
		{
			TIM2->CNT=0;			// 红外接收管脚接收到一个下降沿后，将TIM2计数器清0
		
		}
	} 	
}

void NEC_Decoding(void)//红外解码器
{
	int i,j,k;
		Nec_Flag=0;
	if(Current_bit_CNT>0)
	{
		
		if(Current_bit_CNT>90)		//美的协议       起始码 +A+A‘+B+B'+C+C'+R停止码
		{
				
			for(i=1;i<Current_bit_CNT-40;i++)//美的起始码为8.8ms.找到起始码
		
			{
				if(Each_bit_duration[i]>7000&&Each_bit_duration[i]<9500)//找到起始码
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
										
										Mec_Code[k]&=0XFE;//清除
										Mec_Code[k]|=0X01;//
									if(j!=8)
										Mec_Code[k]<<=1;
								
								}
								else if(Each_bit_duration[i+j]>1000&& Each_bit_duration[i+j]<1250){
									
										Mec_Code[k]&=0XFE;//清除
									if(j!=8)
										Mec_Code[k]<<=1;
										
								}
						}		
						
					
						i+=16;
									
				}
				Current_bit_CNT=0;
			
}
	
		
		}else		if(Current_bit_CNT>40)	//标准协议解码 起始码+16位用户码+八位数据码+八位数据反码+结束码
		{
					
			for(i=1;i<Current_bit_CNT-32;i++)//美的起始码为8.8ms.找到起始码
		
			{
				if(Each_bit_duration[i]>12000&&Each_bit_duration[i]<16000)//找到起始码
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
										
										Mec_Code[k]&=0X7f;//清除
										Mec_Code[k]|=0X80;//
									if(j!=8)
										Mec_Code[k]>>=1;			
								
								}
								else if(Each_bit_duration[i+j]>1000&& Each_bit_duration[i+j]<1250){
										
										
										Mec_Code[k]&=0X7f;//清除
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
