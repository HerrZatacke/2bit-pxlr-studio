#include "./overlayDefs.h"

inline void initOverlays() {
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
}

unsigned char currentOverlay = 1;

inline void showOverlay() {
  for (unsigned char ov = 0; ov < NUM_OVERLAY_SPRITES; ov++) {
    if (currentOverlay == 0) {
      move_sprite(noOverlay[ov]->sprite, noOverlay[ov]->x, noOverlay[ov]->y);
    } else if (currentOverlay == 1) {
      move_sprite(outerBorder[ov]->sprite, outerBorder[ov]->x, outerBorder[ov]->y);
    } else if (currentOverlay == 2) {
      move_sprite(ruleOfThirds[ov]->sprite, ruleOfThirds[ov]->x, ruleOfThirds[ov]->y);
    }
  }
}

inline void hideLowerOverlay() {
  for (unsigned char ov = 0; ov < NUM_OVERLAY_SPRITES; ov++) {
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

inline void hideOverlay() {
  for (unsigned char ov = 0; ov < NUM_OVERLAY_SPRITES; ov++) {
    move_sprite(noOverlay[ov]->sprite, 0, 0);
  }
}
