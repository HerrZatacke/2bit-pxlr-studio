#ifndef DIALOG_H
#define DIALOG_H

#include <gbdk/platform.h>

void appearDialog() BANKED;
void disappearDialog() BANKED;
uint8_t dialog(uint8_t *message, uint8_t handleOverlays) NONBANKED;

#endif
