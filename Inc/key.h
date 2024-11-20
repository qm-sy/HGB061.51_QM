#ifndef __KEY_H_
#define __KEY_H_

#include "stdint.h"

#define   ChannelChoose     2
#define   ModeChoose        4
#define   FunctionKey       3
#define   PowerKey          0
#define   UpKey             1
#define   DownKey           5
#define   FanUp             9
#define   FanDown           13

sbit buzzer = P5^4;

extern uint8_t wind_num;
extern uint8_t power_num;
extern uint8_t mode_num;
extern uint8_t sync_flag;
extern uint8_t mode_info[4];

void button_scan();
void fan_up();
void fan_down();
void up_key();
void down_key();
void channel_choose();
void mode_choose();
void power_key();


#endif 