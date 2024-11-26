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
#include "key.h"
#include "eeprom.h"
#include "sync.h"

void main()
{
    P_SW2 |= 0x80;
    
    GPIOInit();
    ADCInit();
    Uart1Init();
    Tim0Init();
    Tim1Init();
    Tim3Init();
    IT0 = 1;   //ÏÂ½µÑØ´¥·¢¹ýÁã¼ì²âÐÅºÅ
    EX0 = 1;
    EA = 1;
    P42 = 0;
    P23 = 0;
    
    PWM5Init(); 
    P05 = 0;
    wind_crl(0);
      
    printf("======== code start ========\r\n");  
    
    restart:
    delay_ms(1000);
    while(on_off)
    {
        on_off = power_on();
    }  
    P20 = 0; 
    
    
    led_init();    
    lcd_init();  
    ISP_data_init();
    buzzer=buzzer_bit=0;
    
    while(1)
    {
        button_scan();
        fan_rotate();
        external_24V_listen();
        temp_listen();
        power_off();
        if(on_off == 1)
        {
            buzzer=buzzer_bit=0;
            P24 = P25 = P26 = 1;
            P43 = P44 = 1;
            P20 = 1;
            goto restart;   
        }
    }
}