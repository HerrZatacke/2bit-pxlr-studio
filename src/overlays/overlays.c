#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include "defines.h"
#include "globals.h"
#include "overlays/overlayDefs.h"

void initOverlays() BANKED {
  set_sprite_tile(SPRITE_BORDER_H_1, OFFSET_BORDER_H);
  set_sprite_tile(SPRITE_BORDER_H_2, OFFSET_BORDER_H);
  set_sprite_tile(SPRITE_BORDER_H_3, OFFSET_BORDER_H);
  set_sprite_tile(SPRITE_BORDER_H_4, OFFSET_BORDER_H);
  set_sprite_tile(SPRITE_BORDER_H_5, OFFSET_BORDER_H);
  set_sprite_tile(SPRITE_BORDER_H_6, OFFSET_BORDER_H);
  set_sprite_tile(SPRITE_BORDER_H_7, OFFSET_BORDER_H);
  set_sprite_tile(SPRITE_BORDER_H_8, OFFSET_BORDER_H);

  set_sprite_tile(SPRITE_BORDER_V_1, OFFSET_BORDER_V);
  set_sprite_tile(SPRITE_BORDER_V_2, OFFSET_BORDER_V);
  set_sprite_tile(SPRITE_BORDER_V_3, OFFSET_BORDER_V);
  set_sprite_tile(SPRITE_BORDER_V_4, OFFSET_BORDER_V);
  set_sprite_tile(SPRITE_BORDER_V_5, OFFSET_BORDER_V);
  set_sprite_tile(SPRITE_BORDER_V_6, OFFSET_BORDER_V);
  set_sprite_tile(SPRITE_BORDER_V_7, OFFSET_BORDER_V);
  set_sprite_tile(SPRITE_BORDER_V_8, OFFSET_BORDER_V);

  set_sprite_prop(SPRITE_BORDER_H_1, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_H_2, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_H_3, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_H_4, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_H_5, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_H_6, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_H_7, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_H_8, S_PALETTE);

  set_sprite_prop(SPRITE_BORDER_V_1, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_V_2, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_V_3, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_V_4, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_V_5, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_V_6, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_V_7, S_PALETTE);
  set_sprite_prop(SPRITE_BORDER_V_8, S_PALETTE);
}

uint8_t currentOverlay = 1;

void showOverlay() BANKED {
  for (uint8_t ov = 0; ov < NUM_OVERLAY_SPRITES; ov++) {
    if (currentOverlay == 0) {
      move_sprite(noOverlay[ov]->sprite, noOverlay[ov]->x, noOverlay[ov]->y);
    } else if (currentOverlay == 1) {
      move_sprite(outerBorder[ov]->sprite, outerBorder[ov]->x, outerBorder[ov]->y);
    } else if (currentOverlay == 2) {
      move_sprite(ruleOfThirds[ov]->sprite, ruleOfThirds[ov]->x, ruleOfThirds[ov]->y);
    }
  }
}

void hideLowerOverlay() BANKED {
  for (uint8_t ov = 0; ov < NUM_OVERLAY_SPRITES; ov++) {
    if (currentOverlay == 0) {
      if (noOverlay[ov]->y > 99) {
        move_sprite(noOverlay[ov]->sprite, 0, 0);
      }
    } else if (currentOverlay == 1) {
      if (outerBorder[ov]->y > 99) {
        move_sprite(outerBorder[ov]->sprite, 0, 0);
      }
    } else if (currentOverlay == 2) {
      if (ruleOfThirds[ov]->y > 99) {
        move_sprite(ruleOfThirds[ov]->sprite, 0, 0);
      }
    }
  }
}

void hideOverlay() BANKED {
  for (uint8_t ov = 0; ov < NUM_OVERLAY_SPRITES; ov++) {
    move_sprite(noOverlay[ov]->sprite, 0, 0);
  }
}

void nextOverlay() BANKED {
  currentOverlay = (currentOverlay + 1) % NUM_OVERLAYS;
}
