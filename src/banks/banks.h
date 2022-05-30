#ifndef BANKS_H
#define BANKS_H

#include <gbdk/platform.h>
#include "../typedefs/Image.h"

/*
 * Area 0x0000 to 0x2000 in RAM
 * Containing Last seen image, gameface data etc.
 */

//static uint8_t __at(0xA000) last_seen_upper_unused[256];
static uint8_t __at(0xA100) last_seen_upper[1792];
static uint8_t __at(0xA800) last_seen_lower[1792];
//static uint8_t __at(0xAF00) last_seen_padding[256];
//static uint8_t __at(0xB000) game_data_meta_pad_0[434];
static uint8_t __at(0xB1B2) game_data_meta_imageslots[30];
static uint8_t __at(0xB1D0) game_data_meta_magic[5];
static uint8_t __at(0xB1D5) game_data_meta_imageslots_checksum[2];
static uint8_t __at(0xB1D7) game_data_meta_imageslots_echo[30];
static uint8_t __at(0xB1F5) game_data_meta_magic_echo[5];
static uint8_t __at(0xB1FA) game_data_meta_imageslots_echo_checksum[2];
//static uint8_t __at(0xB1FC) game_data_meta[3588];


/*
 * 0x0000 to 0x0035
 * Must be written to RAM bank 16 to control the camera's sensor
 */

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



extern const Image *images[30];
extern uint8_t image_01_unused[];
extern uint8_t image_02_unused[];

#endif
