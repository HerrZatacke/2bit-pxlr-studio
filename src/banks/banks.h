#ifndef BANKS_H
#define BANKS_H

#include <gbdk/platform.h>
#include "../typedefs/Image.h"

extern uint8_t last_seen_upper[];
extern uint8_t last_seen_lower[];

extern uint8_t game_data_meta_imageslots[30];
extern uint8_t game_data_meta_magic[5];
extern uint8_t game_data_meta_imageslots_checksum[2];
extern uint8_t game_data_meta_imageslots_echo[30];
extern uint8_t game_data_meta_magic_echo[5];
extern uint8_t game_data_meta_imageslots_echo_checksum[2];
extern uint8_t game_data_meta[];

extern const Image *images[30];

static volatile uint8_t __at(0xA000) A000;
static uint8_t __at(0xA001) A001;
static uint8_t __at(0xA002) A002;
static uint8_t __at(0xA003) A003;
static uint8_t __at(0xA004) A004;
static uint8_t __at(0xA005) A005;
static uint8_t __at(0xA006) A006A035[48];

extern uint8_t image_01_unused[];
extern uint8_t image_02_unused[];

#endif
