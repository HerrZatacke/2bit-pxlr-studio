#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>

#include "defines.h"
#include "globals.h"
#include "gbcamera.h"
#include "camera.h"
#include "modeShootingManual.h"
#include "modeShootingBurst.h"
#include "modeShootingAssisted.h"
#include "mainMenu.h"
#include "debug.h"
#include "gallery.h"
#include "images.h"

void fastLoadImageTiles() BANKED {
  SWITCH_RAM(0);
  set_data(VRAM_9000, last_seen_upper, HALF_IMAGE_SIZE);
  set_data(VRAM_8000, last_seen_lower, HALF_IMAGE_SIZE);
}

void mainLoop() BANKED {
  // Loop forever
  while (TRUE) {
    switch (mainLoopState) {
      case MAIN_LOOP_SHOOT_MANUAL:
        fastLoadImageTiles();
        manualShootLoop();
        break;
      case MAIN_LOOP_SHOOT_BURST:
        fastLoadImageTiles();
        burstShootLoop();
        break;
      case MAIN_LOOP_SHOOT_ASSISTED:
        fastLoadImageTiles();
        assistedShootLoop();
        break;
      case MAIN_LOOP_MENU:
        mainMenu();
        break;
      case MAIN_LOOP_DEBUG:
        debugMenu();
        break;
      case MAIN_LOOP_IMAGE_GALLERY:
        galleryMenu();
        break;
      case MAIN_LOOP_IMAGE:
        imageMenu();
        break;
    }

    wait_vbl_done();
  }
}
