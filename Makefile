CC	= $(GBDK_FOLDER)/bin/lcc -Wa-l -Wl-m -Wl-j
RU	=  $(GBDK_FOLDER)/romusage/romusage

BIN	= pxlr.gb

all: $(BIN) romusage

obj/banks.o:	src/images.c
	$(CC) -c -o $@ $<

obj/globals.o:	src/globals.c
	$(CC) -c -o $@ $<

obj/values.o:	src/values.c
	$(CC) -c -o $@ $<

obj/main.o:	src/main.c
	$(CC) -c -o $@ $<

obj/camera.o:	src/camera.c
	$(CC) -c -o $@ $<

obj/splash.o:	src/splash.c
	$(CC) -c -o $@ $<

obj/expose.o:	src/expose.c
	$(CC) -c -o $@ $<

obj/gallery.o:	src/gallery.c
	$(CC) -c -o $@ $<

obj/mainMenu.o:	src/mainMenu.c
	$(CC) -c -o $@ $<

obj/mainLoop.o:	src/mainLoop.c
	$(CC) -c -o $@ $<

obj/modeShootingManual.o:	src/modeShootingManual.c
	$(CC) -c -o $@ $<

obj/modeShootingBurst.o:	src/modeShootingBurst.c
	$(CC) -c -o $@ $<

obj/dialog.o:	src/dialog.c
	$(CC) -c -o $@ $<

obj/overlayDefs.o:	src/overlays/overlayDefs.c
	$(CC) -c -o $@ $<

obj/shootingManualMenuItems.o:	src/menus/shootingManualMenuItems.c
	$(CC) -c -o $@ $<

obj/mainMenuItems.o:	src/menus/mainMenuItems.c
	$(CC) -c -o $@ $<

obj/imageMenuItems.o:	src/menus/imageMenuItems.c
	$(CC) -c -o $@ $<

obj/overlays.o:	src/overlays/overlays.c
	$(CC) -c -o $@ $<

obj/bleep.o:	src/bleep.c
	$(CC) -c -o $@ $<

obj/debug.o:	src/debug.c
	$(CC) -c -o $@ $<

obj/utils.o:	src/utils.c
	$(CC) -c -o $@ $<

obj/bankedData.o:	src/bankedData.c
	$(CC) -c -o $@ $<

obj/joypad.o:	src/joypad.c
	$(CC) -c -o $@ $<

obj/imageIndexing.o:	src/imageIndexing.c
	$(CC) -c -o $@ $<

obj/saveImage.o:	src/saveImage.c
	$(CC) -c -o $@ $<

obj/printCmd.o:	src/printCmd.c
	$(CC) -c -o $@ $<

obj/imageInfo.o:	src/imageInfo.c
	$(CC) -c -o $@ $<

obj/frame_pxlr.o: res/frames/frame_pxlr.c
	$(CC) -c -o $@ $<

obj/pxlr-logo.o: res/pxlr-logo.c
	$(CC) -c -o $@ $<

obj/nope.o: res/nope.c
	$(CC) -c -o $@ $<

obj/font.o: res/font.c
	$(CC) -c -o $@ $<

obj/maps.o: res/maps.c
	$(CC) -c -o $@ $<

obj/tiles.o: res/tiles.c
	$(CC) -c -o $@ $<

clean:
	rm -rf obj && rm -f version.h && rm -f branch.h

obj: clean
	mkdir obj

obj/pxlr.sav:
	cp assets/pxlr.sav obj/pxlr.sav

version.h: version
	tr -d '\r\n ' < $< | xxd -u -p -c 1 | sed 's/\s+/_/g' | sed 's/^/  0x/g; s/$$/,/g' | sed -z 's/^/const uint8_t version[] = {\n/g; s/$$/};\n/g' > $@

branch.h:
	git rev-parse --abbrev-ref HEAD | tr -d '\r\n' | sed 's/master/ /g' | xxd -u -p -c 1 | sed 's/\s+/_/g' | sed 's/^/  0x/g; s/$$/,/g' | sed -z 's/^/const uint8_t branch[] = {\n/g; s/$$/};\n/g' > $@

$(BIN):	obj branch.h version.h obj/pxlr.sav obj/printCmd.o obj/pxlr-logo.o obj/font.o obj/maps.o obj/tiles.o obj/nope.o obj/utils.o obj/frame_pxlr.o obj/joypad.o obj/banks.o obj/imageIndexing.o obj/debug.o obj/globals.o obj/bleep.o obj/bankedData.o obj/dialog.o obj/expose.o obj/overlayDefs.o obj/overlays.o obj/values.o obj/shootingManualMenuItems.o obj/saveImage.o obj/imageInfo.o obj/mainMenuItems.o obj/imageMenuItems.o obj/gallery.o obj/mainMenu.o obj/modeShootingManual.o obj/modeShootingBurst.o obj/splash.o obj/camera.o obj/mainLoop.o obj/main.o
	$(CC) -Wl-yt0xFC -Wl-yo16 -Wl-ya16 -Wm-yn"PXLR CAMERA" -o obj/$@ obj/*.o

romusage:
	$(RU) ./obj/pxlr.map
