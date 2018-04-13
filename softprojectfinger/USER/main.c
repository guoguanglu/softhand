/************************************************************************************
Author: Guo Guanglu, Liu Kai, Zhu Xiaokun
Email: 2360889142@qq.com
#project: a softhand project, use air pressure to actuate flexible hands to 
#grab things and visually identify gestures automatically
*************************************************************************************/
#include "stm32f10x.h"
#include "mpu6050.h"
#include "i2c_mpu6050.h"
#include "i2c.h"
#include "timer.h"
#include "delay.h"
#include "LED.h"
#include "usart.h"
#include "adc.h"
#include "finger.h"
int Voltage_D;
float Voltage_A;
int finger[5];
int pose;
int mode=1;//检测是手动还是上位机控制1代表手动0代表上位机控制
int all_in;//实现手动all in
int all_out;//实现手动all out
int all_mode;//判断是mode还是all
int S_mode;//与非检测控制电机
extern	int readbuf[16];
extern int readbuf[16];
extern int vt_mode;
int main(void)
{	
	NVIC_Configuration();
	Init_LEDpin();
  uart_init(38400);
	uart_init3(38400);
	Adc_Init();
	delay_init();
	Init_finger();
	TIM3_Init(4999,7199);//定时器TIM3,1KHZ update duty
	TIM4_PWM_Init(999,71);//1KHZ

//	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//	GPIO_SetBits(GPIOC,GPIO_Pin_14);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_15);
		i2cInit();
	delay_nms(10);
	MPU6050_Init();
//	 printf("\n初始化成功\r\n");
	while(1)
	{	
		 //MPU6050_Pose();
		 Scan_MPU6050();
	  	finger_pose();
//		if(USART_RX_STA3&0x8000)
//		{
//			USART_RX_BUF[0]='1';USART_RX_BUF[1]='0';USART_RX_BUF[2]='0';
//			USART_RX_BUF[3]='0';USART_RX_BUF[4]='0';USART_RX_BUF[5]='0';
//			USART_RX_BUF[6]='1';USART_RX_BUF[7]='5';USART_RX_BUF[8]='0';
//			USART_RX_BUF[9]='1';USART_RX_BUF[10]='7';USART_RX_BUF[11]='0';
//			USART_RX_BUF[12]='1';USART_RX_BUF[13]='5';USART_RX_BUF[14]='0';
//			USART_RX_BUF[15]='1';
//			USART_RX_STA3=0;
//		}
		if(USART_RX_STA&0x8000)
		{
			if(readbuf[15]==1)
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
				GPIO_ResetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12);
				GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
				delay_ms(500);
				finger_read(USART_RX_BUF);
			}else
			{
				finger_read(USART_RX_BUF);
			}
			//delay_ms(40);
					USART_RX_STA=0;
		}
			finger_read(USART_RX_BUF);
			//delay_ms(20);
			all_switch();
		 motorcontrol();
		Voltage_D=Get_Adc_Average(ADC_Channel_0,8);
		//TIM_SetCompare2(TIM4,Voltage_D/1.237);
		if(mode)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
			GPIO_SetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12);
			GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);
		}
		//printf("%d\n%d\n%d\n%d\n%d\n%d",readbuf,finger[0],finger[1],finger[2],finger[3],finger[4]);//发送姿态反馈+五个手指的姿态过去设定值
		//printf("%d\n%d\n%d\n%d\n%d\n%d",readbuf[15],finger[0],finger[1],finger[2],finger[3],finger[4]);
//		delay_ms(100);
		
//		//陀螺仪
//	    printf("\r\nPitch/Roll/Yaw:%f,%f,%f\n",Pitch,Roll,Yaw);   //ROLL
//		  Voltage_D[0]=Get_Adc_Average(0,8);
//			Voltage_A[0]=(float)Voltage_D[0]/4096*3.3;
//			printf("\r\nADC%d输入电压为:\t\t%f\r\n",0,Voltage_A[0]);
//			printf("\r\nADC%d输入数字量电压:\t\t%d\t占空比:\t\t%f\r\n",0,Voltage_D[0],Voltage_D[0]/12.37);
			//int i;
//		for(i=0;i<4;i++)
//		{
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//			Voltage_D[i]=Get_Adc_Average(i,8);
//			Voltage_A[i]=(float)Voltage_D[i]/4096*3.3;
//			//printf("\r\nADC%d输入电压为:\t\t%f\r\n",i,Voltage_A[i]);
//			//delay_ms(5);
//			//printf("\r\n电机占空比:\t\t%f\r\n",Voltage_D/10/1.73);
//			printf("\r\nADC%d输入数字量电压:\t\t%d\t占空比:\t\t%f\r\n",i,Voltage_D[i],Voltage_D[i]/12.37);
//			delay_ms(5);
//		}
//			MPU6050_Pose();
//	    printf("\r\nPitch/Roll/Yaw:%f,%f,%f\n",Pitch,Roll,Yaw);   //ROLL
//	    //delay_ms(200);
	}
}






