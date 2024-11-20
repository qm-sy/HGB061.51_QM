#ifndef __TIMER_H_
#define __TIMER_H_

#include "stdint.h"

extern bit fan_dis_bit;
extern bit zero_bit;
extern bit buzzer_bit;
extern bit scan_stop_bit;
extern bit scan_start_bit;
extern bit tempchannel1;
extern bit tempchannel2;
extern bit tempchannel3;
extern uint8_t channel_num;

void Tim0Init();
void Tim1Init();
void Tim3Init();
void power_crl(uint8_t power_num);

#endif