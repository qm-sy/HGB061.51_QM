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

void main()
{
    uint16_t addr = 0x0200;
    uint8_t i;
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
    ISP_data_init();
    PWMSet(2000);

    printf("========code start========\r\n");
    for(i=0;i<10;i++)
    {
      printf("the value of addr %d \r\n",(int)addr);  
      addr++;
    }
    
    while(1)
    {
        button_scan();
//        fan_leaf1_dis(fan_dis_bit);
//        fan_leaf2_dis(~fan_dis_bit);
 
    }

}