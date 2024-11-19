#include "STC15W4Kxx.h"
#include "pwm.h"

void PWM5Init(void)
{
    P_SW2 |= 0x80;              //��չSFR���ʿ���ʹ��
    PWMCFG = 0x08;              //����PWM5�������ʼ��ƽΪ�ߵ�ƽ
    PWMCKS = 0x0b;              //ѡ��PWM��ʱ��ΪFosc/12
    
    PWMC = CYCLE;               //����PWM���� PWMCH PWMCL
    
    PWM5T1 = 0;                 //����PWM5��1�η�ת��PWM����
    PWM5T2 = 10;                //����PWM5��2�η�ת��PWM���� ռ�ձ�Ϊ(PWM5T2-PWM5T1)/PWMC
                         
    PWM5CR = 0x00;              //ѡ��PWM5�����P2.3,��ʹ��PWM5�ж�
    
    PWMFDCR=0x30;               //��PWM�ⲿ�쳣���ܲ�����PWM�ⲿ�쳣ʱ��PWM�����������������Ϊ��������ģʽ
}

void PWMSet(unsigned int dat)
{
    PWM5T2 = dat;
}

void PWMStart(void)
{
    PWMCR = 0X88;
}

void PWMStop(void)
{
    PWMCR = 0X00;
}
