#ifndef __EEPROM_H_
#define __EEPROM_H_

#include "stdint.h"

void ISPIdle();

uint8_t ISP_read(uint16_t addr);

void ISP_write(uint16_t addr,uint8_t dat);

void ISP_earse(uint16_t addr);

#endif