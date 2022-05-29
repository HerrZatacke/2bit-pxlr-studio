#include <gb/gb.h>
#include <gbdk/platform.h>

#include "./joypad.h"
#include "./bankedData.h"
#include "./defines.h"
#include "../version.h"
#include "../branch.h"
#include "../res/pxlr-logo.h"

unsigned char splash() {

  set_data_banked(VRAM_9000, logo_tiles, LOGO_TILE_COUNT * 16, 1);
  set_data_banked(VRAM_8000, logo_tiles, LOGO_TILE_COUNT * 16, 1);

  set_bkg_tiles_banked(0, 0, 20, 18, logo_map, 1);

  set_bkg_based_tiles(0, 16, sizeof(branch), 1, branch, OFFSET_FONT - 32);
  set_bkg_based_tiles(0, 17, sizeof(version), 1, version, OFFSET_FONT - 32);
  set_bkg_based_tiles(13, 16, 7, 2, "Shoot A Menu B", OFFSET_FONT - 32);

  while (jp != J_A && jp != J_B) {
    wait_vbl_done();
  }

  unsigned char result = jp;

  waitRelease(); // waitRelease() resets `jp`

  return result;
}
