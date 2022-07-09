#ifndef __SHUTTER_H_INCLUDE__
#define __SHUTTER_H_INCLUDE__

#include <gbdk/platform.h>
#include <stdint.h>

#define SHUTTER_ACTIVATE    TRUE
#define SHUTTER_SUSPEND     FALSE

extern volatile uint8_t shutter_value;

inline uint8_t check_and_reset_shutter() {
    uint8_t res = shutter_value;
    shutter_value = 0;
    return res;
}

void init_shutter() BANKED;
uint8_t activate_shutter(uint8_t value) BANKED;

#endif