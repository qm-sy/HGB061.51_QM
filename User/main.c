#include "STC15W4Kxx.h"
#include <stdio.h> 
#include "gpio.h"
#include "delay.h"
#include "adc.h"
#include "uart.h"
#include "ntc.h"
#include "timer.h"
#include "screen.h"
#include "stdint.h"
#include "pwm.h"

unsigned char temp_num = 0;
void main()
{
    P_SW2 |= 0x80;
    
    GPIOInit();
    ADCInit();
    Uart1Init();
    Tim0Init();
    Tim1Init();
    Tim3Init();
    EA = 1;
    P20 = 0;
    P23 = 0;
    PWM5Init();
    
    PWMStart();
    
    lcd_init();
    wind_dis(6);
    num_dis(123);
    channel_dis(6);
    sun_dis(DIS_ON);
    sync_dis(DIS_ON);
    alarm_dis(DIS_ON);
    F_dis(DIS_ON);
    M_dis(DIS_ON);
    R_dis(DIS_ON);
    Celsius_dis(DIS_ON);
    mode_dis(DIS_ON);
    percentage_dis(DIS_ON);
    cur_dis(DIS_ON);
    set_dis(DIS_ON);
    fan_center_dis(DIS_ON);
     PWMSet(20);
    printf("========code start========\r\n");

    while(1)
    {

        fan_leaf1_dis(fan_dis_bit);
        fan_leaf2_dis(~fan_dis_bit);

        
    }

}