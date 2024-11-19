#include "STC15W4Kxx.h"
#include "eeprom.h"
#include "stdint.h"
#include "delay.h"

void ISPIdle()
{
    IAP_CONTR = 0X00;
    IAP_CMD = 0X00;
    IAP_TRIG = 0X00;
    IAP_ADDRH = 0X80;
    IAP_ADDRL = 0X00; 
}

uint8_t ISP_read(uint16_t addr)
{
    uint8_t dat;
    
    IAP_CONTR = 0X83;
    IAP_CMD = 0X01;
    IAP_ADDRL = addr;
    IAP_ADDRH = addr>>8;
    
    IAP_TRIG = 0X5A;
    IAP_TRIG = 0XA5;
    
    delay_ms(10);
    
    dat = IAP_DATA;
    
    ISPIdle();
    
    return dat;
}

void ISP_write(uint16_t addr,uint8_t dat)
{
    IAP_CONTR = 0X83;
    IAP_CMD = 0X02;
    IAP_ADDRL = addr;
    IAP_ADDRH = addr>>8;
    IAP_DATA = dat;
    
    IAP_TRIG = 0X5A;
    IAP_TRIG = 0XA5;
    
    delay_ms(10);
    
    ISPIdle();
}

void ISP_earse(uint16_t addr)
{   
    IAP_CONTR = 0X83;   //  WT2:WT1:WT0 = 0 1 1  CPUµÈ´ýÊ±¼ä>=12MHz
    IAP_CMD = 0X03;
    IAP_ADDRL = addr;
    IAP_ADDRH = addr>>8;
    
    IAP_TRIG = 0X5A;
    IAP_TRIG = 0XA5;
    
    delay_ms(10);
    
    ISPIdle();
}
