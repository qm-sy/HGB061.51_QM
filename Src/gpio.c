#include "STC15W4Kxx.h"
#include "gpio.h"

void GPIOInit()
{
    P1M0 = 0X00;    P1M1 = 0X00;       //P1.0 P1.1 P1.4为高阻输入
    P2M0 = 0x09;    P2M1 = 0x00;       //P2.0 2.3为推挽      
    P3M0 = 0X00;    P3M1 = 0X00;       
    P5M0 = 0X10;    P5M1 = 0X00;       //P5.4为推挽
    
}
  