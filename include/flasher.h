#ifndef __FLASHER_H_INCLUDE
#define __FLASHER_H_INCLUDE

#include <stdint.h>

void restore_sram_bank(uint8_t bank);
void restore_sram();

uint8_t save_sram();

#endif