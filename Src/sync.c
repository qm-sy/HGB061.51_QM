#include "STC15W4Kxx.h"
#include "stdint.h"
#include "sync.h"
#include "timer.h"
#include "key.h"
#include "pwm.h"
#include "ntc.h"
#include "screen.h"
#include "stdio.h"

void sync_judge()
{
    if(sync_bit==1)
    {
        if(external_24bit==1)
        {
            power_bit = 1;
            wind_bit = 1;
        }
        else
        {
            power_bit = 0;
            wind_bit = 0;
            PWMStop();
        }
    }
    else
    {
        power_bit = 1;
        wind_bit = 1; 
    }
    
    power_crl(power_num);
    wind_crl(wind_num);         //刷新风力和功率
}

void led_init()
{
    P24 = P25 = P26 = 0;
    P43 = P44 = 0;
}

void external_24V_listen()
{
    static now_value = 0;
    if(now_value!=previous_value)
    {
        sync_judge();
        now_value = previous_value;
    }
}

void temp_listen()
{   
    static uint8_t temp; 
    temp = (uint8_t)get_temp(6);
    if(temp>=temp_num)
    {
        alarm_dis(DIS_ON);
        P05 = 1;
    }
    
    if(temp<temp_num)    
    {
        if(sync_bit==0)
        {
            alarm_dis(DIS_OFF);
            P05 = 0;
        }
        if(sync_bit==1)
        {
            if(external_24bit==1)
            {
                alarm_dis(DIS_OFF);
                P05 = 0; 
            }
        }
    }

    
//    if(sync_bit==1)
//        
//    {
//        if(external_24bit==1)
//        {
//            //alarm_dis(DIS_OFF);
//            power_bit = 1; 
//        }
//    }
}