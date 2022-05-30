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

// Camera hardware register: Capture
static volatile uint8_t __at(0xA000) CAM_REG_CAPTURE;
// Camera hardware register: EdgeExclusive, EdgeOperation, Gain
static uint8_t __at(0xA001) CAM_REG_EDEXOPGAIN;
// Camera hardware register: Exposure Time
static uint16_t __at(0xA002) CAM_REG_EXPTIME;
// Camera hardware register: Edge Ratio, Invert Output, Voltage Ref
static uint8_t __at(0xA004) CAM_REG_EDRAINVVREF;
// Camera hardware register: Zero Points, Voltage Out
static uint8_t __at(0xA005) CAM_REG_ZEROVOUT;
// Camera hardware register: Dither Pattern (48 bytes)
static uint8_t __at(0xA006) CAM_REG_DITHERPATTERN[48];

extern uint8_t image_01_unused[];
extern uint8_t image_02_unused[];

#endif
