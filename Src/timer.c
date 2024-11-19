#include "STC15W4Kxx.h"
#include "timer.h"
#include "stdint.h"

bit fan_dis_bit = 0;
void Tim0Init()  //11.0592Mhz  1ms
{
    AUXR |= 0X80;   //�޸ļ������ʣ���ʱ��ʱ������Ϊ12Tģʽ
	
	TMOD &= 0XF0;   //���TIM0��Ҫ���õĵ���λ������λ��TIM0,����λ��TIM1��

	TH0 = 0XCD;   // TH0 ����λ  TL0 ����λ
	TL0 = 0XD4;   //ͨ������ó���ֵ�����㹫ʽ������
	
	TF0 = 0;  //���TC0N-TF0  �ж������־��������Զ���1��CPU��Ӧ�жϺ���Ӳ����0
	TR0 = 1;  //TCON-TR0  TIM0��ʼ��������

	ET0 = 1;   //��IE-ET0��TIM0�ж�
}


void Tim1Init()  //11.0592Mhz  10ms  16λ�ֶ�װ��
{   
	AUXR &= 0xBF;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;			//���ö�ʱ��ģʽ
	//TMOD |= 0x10;			//���ö�ʱ��ģʽ   �ֶ�/�Զ�����
    
    TL1 = 0x00;				//���ö�ʱ��ʼֵ
	TH1 = 0xDC;				//���ö�ʱ��ʼֵ
	TF1 = 0;				//���TF1��־
	TR1 = 1;				//��ʱ��1��ʼ��ʱ

    ET1 = 1; //��IE-ET1��TIM1�ж�
}

void Tim3Init(void)		//10����@11.0592MHz
{
	T4T3M &= 0xFD;			//��ʱ��ʱ��12Tģʽ
	T3L = 0x00;				//���ö�ʱ��ʼֵ
	T3H = 0xDC;				//���ö�ʱ��ʼֵ
	T4T3M |= 0x08;			//��ʱ��3��ʼ��ʱ
    
    IE2 |= 0x20; //��IE2-ET2��TIM3�ж�
}
void Tim0Isr(void) interrupt 1 
{

}

void Tim1Isr(void) interrupt 3 
{
    static uint8_t i = 0;
    i++;
    if(i>15)
    {
        fan_dis_bit = ~fan_dis_bit;
        i = 0;
    }
}
void Tim3Isr(void) interrupt 19 
{

}