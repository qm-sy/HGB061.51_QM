#include "STC15W4Kxx.h"
#include "timer.h"
#include "stdint.h"
#include "key.h"

bit fan_dis_bit = 0;
bit zero_bit = 0;
bit buzzer_bit = 1;
bit scan_stop_bit = 1;
bit scan_start_bit = 0;
bit tempchannel1 = 1;
bit tempchannel2 = 1;
bit tempchannel3 = 1;
uint8_t channel_num = 1;
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
	TMOD |= 0x10;			//���ö�ʱ��ģʽ   �ֶ�/�Զ�����
    
//    TL1 = 0x00;				//���ö�ʱ��ʼֵ
//	TH1 = 0xDC;				//���ö�ʱ��ʼֵ
//	TF1 = 0;				//���TF1��־
//	TR1 = 1;				//��ʱ��1��ʼ��ʱ

//    ET1 = 1; //��IE-ET1��TIM1�ж�
}

void Tim3Init(void)		//10����@11.0592MHz
{
	T4T3M &= 0xFD;			//��ʱ��ʱ��12Tģʽ
	T3L = 0x00;				//���ö�ʱ��ʼֵ
	T3H = 0xDC;				//���ö�ʱ��ʼֵ
	T4T3M |= 0x08;			//��ʱ��3��ʼ��ʱ
    
    IE2 |= 0x20; //��IE2-ET2��TIM3�ж�
}

void ET0ISR(void) interrupt 0 
{
    tempchannel1 = tempchannel2 = tempchannel3 = 1;    
        /*��ʱ����*/
    TL1 = 65520;				//���ö�ʱ��ʼֵ
	TH1 = 65520>>8;				//���ö�ʱ��ʼֵ

    zero_bit = 1;
    
    TR1 = 1;				//��ʱ��1��ʼ��ʱ      
    ET1 = 1; 
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
    
    if(zero_bit == 1)
    {
        switch(channel_num)
        {
            case 1: {tempchannel1=0;}break;
            case 2: {tempchannel1=0; tempchannel2=0;}break;
            case 3: {tempchannel1=0; tempchannel2=0; tempchannel3=0;}break;
            case 4: {tempchannel1=0; tempchannel3=0;}break;
            case 5: {tempchannel2=0; tempchannel3=0;}break;
            case 6: {tempchannel2=0;}break;
            case 7: {tempchannel3=0;}break;
        }
            /*����һ��10us������*/
            zero_bit = 0; 

            TL1 = 0xF7;				//���ö�ʱ��ʼֵ
            TH1 = 0xFF;				//���ö�ʱ��ʼֵ
    }
  
    else
    {
        tempchannel1 = tempchannel2 = tempchannel3 = 1;     //1-0-1������ 2us
        TR1 = 0;				//��ʱ���رռ�ʱ      
        ET1 = 0; 
    }
}

void Tim3Isr(void) interrupt 19 
{
    static uint8_t buzzer_continue_cnt = 0;
    static uint8_t sacn_cnt = 0;
    if(buzzer_bit==0)
    {
        buzzer_continue_cnt++;
        if(buzzer_continue_cnt>10)
        {
            buzzer_continue_cnt=0; 
            buzzer=buzzer_bit=1;
        }
    } 
    
    if(scan_stop_bit == 1)
    {
        sacn_cnt++;
        if(sacn_cnt>10)
        {
            scan_start_bit = 1;
            scan_stop_bit = 0;
            sacn_cnt = 0;
        }
    }
}

void power_crl(uint8_t power_num)
{
    static uint16_t tim1_t;
    tim1_t = power_num*64+58400;
    TL1 = tim1_t;                   //���ö�ʱ��ʼֵ
    TH1 = tim1_t>>8;				//���ö�ʱ��ʼֵ
}