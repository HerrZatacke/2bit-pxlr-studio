#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>

#include "joypad.h"
#include "bankedData.h"
#include "defines.h"
#include "utils.h"
#include "logo.h"

#define Q(x) #x
#define QUOTE(x) Q(x)

static const uint8_t branch[] = QUOTE(BRANCH);
static const uint8_t version[] = QUOTE(VERSION);


uint8_t splash() BANKED {
  HIDE_SPRITES;
  BGP_REG = PALETTE_BLANK;

  set_data_banked(VRAM_9000, logo_tiles, logo_TILE_COUNT * 16, BANK(logo));
  set_data_banked(VRAM_8000, logo_tiles, logo_TILE_COUNT * 16, BANK(logo));

  set_bkg_tiles_banked(0, 0, 20, 18, logo_map, 1);

  set_bkg_based_tiles(0, 16, sizeof(branch) - 1, 1, branch, OFFSET_FONT - 32);
  set_bkg_based_tiles(0, 17, sizeof(version) - 1, 1, version, OFFSET_FONT - 32);
  set_bkg_based_tiles(13, 16, 7, 2, "Shoot A Menu B", OFFSET_FONT - 32);

  fadeIn();

  while (jp != J_A && jp != J_B) {
    wait_vbl_done();
  }

  uint8_t result = jp;

  waitRelease(); // waitRelease() resets `jp`

  fadeOut();
  pause(15);
  SHOW_SPRITES;

  return result;
}
