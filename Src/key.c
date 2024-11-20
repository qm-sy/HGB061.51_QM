#include "STC15W4Kxx.h"
#include "key.h"
#include "stdint.h"
#include "timer.h"
#include "pwm.h"
#include "screen.h"
#include "delay.h"
#include "eeprom.h"
#include "stdio.h"

uint8_t wind_num = 0;
uint8_t power_num = 0;
uint8_t mode_num = 0;
uint8_t sync_flag = 0;

void button_scan()
{
    uint8_t key_val = (P0&0X0f);
    if(scan_start_bit == 1)
    {
        switch(key_val)
        {
            case PowerKey:
                power_key();
                break;
            
            case UpKey:
                up_key();
                delay_ms(50);
                break;
            
            case ChannelChoose:
                channel_choose();
                delay_ms(50);
                break;
//            case FunctionKey:
            
            case ModeChoose:
                mode_choose();
                delay_ms(50);
                break;
                
            case DownKey:
                down_key();
                delay_ms(50);
                break;
            
            case FanUp:
                fan_up();   
                delay_ms(50); 
                break;
            
            case FanDown:
                fan_down();          
                delay_ms(50);
                break;

        }
        scan_stop_bit = 1;
        scan_start_bit = 0;
    }
}

void fan_up()
{
    buzzer=buzzer_bit=0;
    wind_num += 1;
    if(wind_num>6)
    {
        wind_num = 6;
    }
    wind_crl(wind_num);
    wind_dis(wind_num);
    
    eeprom_data_write();
}

void fan_down()
{
    buzzer=buzzer_bit=0;
    wind_num -= 1;
    if(wind_num<0)
    {
        wind_num = 0;
    }
    wind_crl(wind_num);
    wind_dis(wind_num);
    
    eeprom_data_write();
}

void up_key()
{
    char up_num = 0;
//    uint8_t dat;
    up_num = power_num;
    buzzer=buzzer_bit=0;
    up_num += 5;
    if(up_num>100)
    {
        up_num = 100;
    }
    power_num = up_num;
    power_crl(power_num);
    num_dis(power_num);
    
    eeprom_data_write();
    printf("THE value of mode_info[0] is %d \r\n",(int)mode_info[0]);
    printf("THE value of mode_info[2] is %d \r\n",(int)mode_info[2]);
    printf("THE value of mode_info[3] is %d \r\n",(int)mode_info[3]);
    
//    dat = ISP_read(0x0200);
//    printf("THE value of mode_info[0] is %d \r\n",(int)dat);
//    
    
}

void down_key()
{
    char down_num = 0;
    down_num = power_num;
    buzzer=buzzer_bit=0;
    down_num -= 5;
    if(down_num<0)
    {
        down_num = 0;
    }
    power_num = down_num;
    power_crl(power_num);
    num_dis(power_num);
    
    eeprom_data_write();
}

void channel_choose()
{
    buzzer=buzzer_bit=0;
    
    if(channel_num==7)
    {
        channel_num = 1;
    }
    else
    {
        channel_num += 1;
    }
    channel_dis(channel_num);
    
    eeprom_data_write();
}

void mode_choose()
{
    buzzer=buzzer_bit=0;
    if(mode_num==5)
    {
        mode_num = 1;
    }
    else
    {
        mode_num += 1;
    }
    
    lcd_clear();
    mode_dis(DIS_ON);
    num_dis(mode_num);
    percentage_dis(DIS_OFF);
    
    eeprom_data_read(mode_num);
    
    delay_ms(1000);
    
    mode_dis(DIS_OFF);
    sun_dis(DIS_ON);
    printf("THE value of mode_info[0] is %d \r\n",(int)mode_info[0]);
    printf("THE value of mode_info[2] is %d \r\n",(int)mode_info[2]);
    printf("THE value of mode_info[3] is %d \r\n",(int)mode_info[3]);
    channel_dis(mode_info[0]);
    num_dis(mode_info[3]);
    percentage_dis(DIS_ON);
    wind_dis(mode_info[2]);
    
    eeprom_mode_save();
 
}

void power_key()
{
   lcd_clear();
}