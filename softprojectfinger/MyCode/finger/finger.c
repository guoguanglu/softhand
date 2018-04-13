#include "finger.h"
#include "led.h"
#include "delay.h"
#include "mpu6050.h"
#include "usart.h"
#include "i2c_mpu6050.h"
int MPU6050[5];
extern int Voltage_D;
extern int mode;
extern int all_in;
extern int all_out;
extern int all_mode;
extern int S_mode;
void Init_finger(void)
{
	//PA1,4,5,6,7,8,11��12,PB0,1,�����ֵ�ʮ������,
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PF�˿�ʱ��
//PB5��PC15��PC14��PA2��PA3Ϊ�����ǵ������ַ�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOc
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//PA15Ϊall	_mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//PB14��⿪��ģʽ���Ƶ��PB15��������������ǽṹ�����Ƶ��ģʽ//PB12��PB13ʵ�֡�all_in��all_out
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3);
	GPIO_ResetBits(GPIOC,GPIO_Pin_14| GPIO_Pin_15);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15);					//��ʼ������Ϊ1
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_12|GPIO_Pin_13);
}
int vt_mode;
int readbuf[16];
void finger_read(u8*buf)
{
	int i;
//	int vt_mode;

	//���buf����
	for(i=0;i<16;i++)
	{
		readbuf[i]=buf[i]-48;
	}
	if(readbuf[15]==1)//����ģʽλ0λ��ťģʽ1λ������̬ģʽ
	{
			finger[0]=readbuf[2]+readbuf[1]*10+readbuf[0]*100;//��ָ1
			finger[1]=readbuf[5]+readbuf[4]*10+readbuf[3]*100;//��ָ2
			finger[2]=readbuf[8]+readbuf[7]*10+readbuf[6]*100;//��ָ3
			finger[3]=readbuf[11]+readbuf[10]*10+readbuf[9]*100;//��ָ4
			finger[4]=readbuf[14]+readbuf[13]*10+readbuf[12]*100;//��ָ5
			if(MPU6050[0]<finger[0])                                                                                                                                                                                                 
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
				GPIO_SetBits(GPIOA,GPIO_Pin_8);
			}else
			{
				  GPIO_SetBits(GPIOA,GPIO_Pin_1);
					GPIO_SetBits(GPIOA,GPIO_Pin_8);
			}
						if(MPU6050[1]<finger[1])                                                                                                                                                                                                 
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOA,GPIO_Pin_11);
			}else
			{
				  GPIO_SetBits(GPIOA,GPIO_Pin_4);
					GPIO_SetBits(GPIOA,GPIO_Pin_11);
			}
						if(MPU6050[2]<finger[2])                                                                                                                                                                                                 
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOA,GPIO_Pin_12);
			}else
			{
				  GPIO_SetBits(GPIOA,GPIO_Pin_5);
					GPIO_SetBits(GPIOA,GPIO_Pin_12);
			}
						if(MPU6050[3]<finger[3])                                                                                                                                                                                                 
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOB,GPIO_Pin_0);
			}else
			{
				  GPIO_SetBits(GPIOA,GPIO_Pin_6);
					GPIO_SetBits(GPIOB,GPIO_Pin_0);
			}
						if(MPU6050[4]<finger[4])                                                                                                                                                                                                 
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOB,GPIO_Pin_1);
			}else
			{
				  GPIO_SetBits(GPIOA,GPIO_Pin_7);
					GPIO_SetBits(GPIOB,GPIO_Pin_1);
			}
		
	}else
	{
		//���밴ťģʽ�����ǽ��������Ƿ�����
		 vt_mode=readbuf[14]+readbuf[13]*10;
		if(readbuf[0]==0)//����������0������1
		{	
//			LED1=0;
			switch(vt_mode)
			{
				//��ָ1
				case 1: GPIO_ResetBits(GPIOA,GPIO_Pin_1);break;//��
				case 2: GPIO_SetBits(GPIOA,GPIO_Pin_1);break;//ͣ
				//��ָ2
				case 3: GPIO_ResetBits(GPIOA,GPIO_Pin_4);break;
				case 4: GPIO_SetBits(GPIOA,GPIO_Pin_4);break;
					//��ָ3
				case 5: GPIO_ResetBits(GPIOA,GPIO_Pin_5);break;
				case 6: GPIO_SetBits(GPIOA,GPIO_Pin_5);break;
				//��ָ4
				case 7: GPIO_ResetBits(GPIOA,GPIO_Pin_6);break;
				case 8: GPIO_SetBits(GPIOA,GPIO_Pin_6);break;
				//��ָ5
				case 9: GPIO_ResetBits(GPIOA,GPIO_Pin_7);break;
				case 10: GPIO_SetBits(GPIOA,GPIO_Pin_7);break;
				//ȫ��
				case 11:GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);break;
				case 12:GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);break;
				
			}
		}else//������
		{
//			LED1=1;
				switch(vt_mode)
			{
				//��ָ1
				case 1: GPIO_ResetBits(GPIOA,GPIO_Pin_8);break;//��
				case 2: GPIO_SetBits(GPIOA,GPIO_Pin_8);break;//ͣ
				//��ָ2
				case 3: GPIO_ResetBits(GPIOA,GPIO_Pin_11);break;
				case 4: GPIO_SetBits(GPIOA,GPIO_Pin_11);break;
					//��ָ3
				case 5: GPIO_ResetBits(GPIOA,GPIO_Pin_12);break;
				case 6: GPIO_SetBits(GPIOA,GPIO_Pin_12);break;
				//��ָ4
				case 7: GPIO_ResetBits(GPIOB,GPIO_Pin_0);break;
				case 8: GPIO_SetBits(GPIOB,GPIO_Pin_0);break;
				//��ָ5
				case 9: GPIO_ResetBits(GPIOB,GPIO_Pin_1);break;
				case 10: GPIO_SetBits(GPIOB,GPIO_Pin_1);break;
								//ȫ��
				case 11: 
								GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12);
				        GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
								break;
				case 12: 
								GPIO_SetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12);
				        GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
								break;

			}
		}
		
	}
}
void motorcontrol(void)
{
	mode=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
	S_mode=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
	if(!mode)//mode=0,��λ�����ƣ�mode=1�ֶ�����
	{
		LED1=0;
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7))
		{
			//LED1=0;		
			TIM_SetCompare2(TIM4,0);
		}else
		{
			//LED1=1;		
			TIM_SetCompare2(TIM4,Voltage_D/1.237);
		}
	}else
	{
		LED1=1;
		if(S_mode)//S_mode=0,�򿪵����S_mode=1���رյ��
		{
			//LED1=0;
			TIM_SetCompare2(TIM4,0);	
		}else
		{
			//LED1=1;
			TIM_SetCompare2(TIM4,Voltage_D/1.237);
		}
		
	}
}
void all_switch(void)
{
	all_in=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);
	all_out=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	all_mode=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
	if(all_mode)
	{
			if(!all_in)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
		}
		if(!all_out)
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12);
				GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
		}
	}
}

void Scan_MPU6050(void)
{
	int i;
	//MPU6050_1
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_14);
		GPIO_SetBits(GPIOC,GPIO_Pin_15);
	  GPIO_SetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	for(i=0;i<150;i++)
	{	
		MPU6050_Pose();
	}
	if((int)Roll<0)
	{
		MPU6050[0]=(int)Roll+360;
	}else
	{
		MPU6050[0]=(int)Roll;
	}
//		//MPU6050_2
		GPIO_ResetBits(GPIOC,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_15);
	  GPIO_SetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	for(i=0;i<150;i++)
	{	
		MPU6050_Pose();
	}
	if((int)Roll<0)
	{
		MPU6050[1]=(int)Roll+360;
	}else
	{
		MPU6050[1]=(int)Roll;
	}
//			//MPU6050_3
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_14);
	  GPIO_SetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	for(i=0;i<150;i++)
	{	
		MPU6050_Pose();
	}
	if((int)Roll<0)
	{
		MPU6050[2]=(int)Roll+360;
	}else
	{
		MPU6050[2]=(int)Roll;
	}
	
//				//MPU6050_4
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_14);
	  GPIO_SetBits(GPIOC,GPIO_Pin_15);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	for(i=0;i<150;i++)
	{	
		MPU6050_Pose();
	}
	if((int)Roll<0)
	{
		MPU6050[3]=(int)Roll+360;
	}else
	{
		MPU6050[3]=(int)Roll;
	}
					//MPU6050_5
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_14);
	  GPIO_SetBits(GPIOC,GPIO_Pin_15);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	for(i=0;i<150;i++)
	{	
		MPU6050_Pose();
	}
	if((int)Roll<0)
	{
		MPU6050[4]=(int)Roll+360;
	}else
	{
		MPU6050[4]=(int)Roll;
	}
	
	
}
void finger_pose(void)
{
	int i;
	if(USART_RX_STA3&0x8000)
		{
					i= USART_RX_BUF3[0]-48;
			switch(i)
			{
				case 1: 
							USART_RX_BUF[0]='1';USART_RX_BUF[1]='0';USART_RX_BUF[2]='0';
							USART_RX_BUF[3]='0';USART_RX_BUF[4]='0';USART_RX_BUF[5]='0';
							USART_RX_BUF[6]='1';USART_RX_BUF[7]='5';USART_RX_BUF[8]='0';
							USART_RX_BUF[9]='1';USART_RX_BUF[10]='7';USART_RX_BUF[11]='0';
							USART_RX_BUF[12]='1';USART_RX_BUF[13]='5';USART_RX_BUF[14]='0';
							USART_RX_BUF[15]='1';
							break;
				case 2:	
							USART_RX_BUF[0]='1';USART_RX_BUF[1]='0';USART_RX_BUF[2]='0';
							USART_RX_BUF[3]='0';USART_RX_BUF[4]='0';USART_RX_BUF[5]='0';
							USART_RX_BUF[6]='0';USART_RX_BUF[7]='0';USART_RX_BUF[8]='0';
							USART_RX_BUF[9]='1';USART_RX_BUF[10]='7';USART_RX_BUF[11]='0';
							USART_RX_BUF[12]='1';USART_RX_BUF[13]='5';USART_RX_BUF[14]='0';
							USART_RX_BUF[15]='1';
							break;
				case 3: 
							USART_RX_BUF[0]='1';USART_RX_BUF[1]='0';USART_RX_BUF[2]='0';
							USART_RX_BUF[3]='0';USART_RX_BUF[4]='0';USART_RX_BUF[5]='0';
							USART_RX_BUF[6]='0';USART_RX_BUF[7]='0';USART_RX_BUF[8]='0';
							USART_RX_BUF[9]='0';USART_RX_BUF[10]='0';USART_RX_BUF[11]='0';
							USART_RX_BUF[12]='1';USART_RX_BUF[13]='5';USART_RX_BUF[14]='0';
							USART_RX_BUF[15]='1';
							break;
				case 4: 
							USART_RX_BUF[0]='1';USART_RX_BUF[1]='0';USART_RX_BUF[2]='0';
							USART_RX_BUF[3]='0';USART_RX_BUF[4]='0';USART_RX_BUF[5]='0';
							USART_RX_BUF[6]='0';USART_RX_BUF[7]='0';USART_RX_BUF[8]='0';
							USART_RX_BUF[9]='0';USART_RX_BUF[10]='0';USART_RX_BUF[11]='0';
							USART_RX_BUF[12]='0';USART_RX_BUF[13]='0';USART_RX_BUF[14]='0';
							USART_RX_BUF[15]='1';
							break;
				case 5:
							USART_RX_BUF[0]='0';USART_RX_BUF[1]='0';USART_RX_BUF[2]='0';
							USART_RX_BUF[3]='0';USART_RX_BUF[4]='0';USART_RX_BUF[5]='0';
							USART_RX_BUF[6]='0';USART_RX_BUF[7]='0';USART_RX_BUF[8]='0';
							USART_RX_BUF[9]='0';USART_RX_BUF[10]='0';USART_RX_BUF[11]='0';
							USART_RX_BUF[12]='0';USART_RX_BUF[13]='0';USART_RX_BUF[14]='0';
							USART_RX_BUF[15]='1';
							break;
			}
					USART_RX_STA3=0;
		}
}
