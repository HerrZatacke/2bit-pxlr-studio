#ifndef DIALOG_H
#define DIALOG_H

#include <gbdk/platform.h>

void appearDialog() BANKED OLDCALL;
void disappearDialog() BANKED OLDCALL;
unsigned char dialog(unsigned char *message) BANKED OLDCALL;

#endif
