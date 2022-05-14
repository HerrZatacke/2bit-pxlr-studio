CC	= $(GBDK_FOLDER)/bin/lcc -Wa-l -Wl-m -Wl-j

BIN	= pxlr.gb

all:	$(BIN)

obj/bank_00.o:	src/banks/bank_00.c
	$(CC) -Wf-ba0 -c -o $@ $<

obj/bank_01.o:	src/banks/bank_01.c
	$(CC) -Wf-ba1 -c -o $@ $<

obj/bank_02.o:	src/banks/bank_02.c
	$(CC) -Wf-ba2 -c -o $@ $<

obj/bank_03.o:	src/banks/bank_03.c
	$(CC) -Wf-ba3 -c -o $@ $<

obj/bank_04.o:	src/banks/bank_04.c
	$(CC) -Wf-ba4 -c -o $@ $<

obj/bank_05.o:	src/banks/bank_05.c
	$(CC) -Wf-ba5 -c -o $@ $<

obj/bank_06.o:	src/banks/bank_06.c
	$(CC) -Wf-ba6 -c -o $@ $<

obj/bank_07.o:	src/banks/bank_07.c
	$(CC) -Wf-ba7 -c -o $@ $<

obj/bank_08.o:	src/banks/bank_08.c
	$(CC) -Wf-ba8 -c -o $@ $<

obj/bank_09.o:	src/banks/bank_09.c
	$(CC) -Wf-ba9 -c -o $@ $<

obj/bank_10.o:	src/banks/bank_10.c
	$(CC) -Wf-ba10 -c -o $@ $<

obj/bank_11.o:	src/banks/bank_11.c
	$(CC) -Wf-ba11 -c -o $@ $<

obj/bank_12.o:	src/banks/bank_12.c
	$(CC) -Wf-ba12 -c -o $@ $<

obj/bank_13.o:	src/banks/bank_13.c
	$(CC) -Wf-ba13 -c -o $@ $<

obj/bank_14.o:	src/banks/bank_14.c
	$(CC) -Wf-ba14 -c -o $@ $<

obj/bank_15.o:	src/banks/bank_15.c
	$(CC) -Wf-ba15 -c -o $@ $<

obj/bank_16.o:	src/banks/bank_16.c
	$(CC) -Wf-ba16 -c -o $@ $<

obj/main.o:	src/main.c
	$(CC) -c -o $@ $<

obj/printCmd.o:	src/printCmd.c
	$(CC) -c -o $@ $<

clean:
	rm -rf obj && rm -f version.h && rm -f branch.h

obj: clean
	mkdir obj

obj/pxlr.sav:
	cp assets/pxlr.sav obj/pxlr.sav

version.h: version
	tr -d '\r\n ' < $< | xxd -u -p -c 1 | sed 's/\s+/_/g' | sed 's/^/  0x/g; s/$$/,/g' | sed -z 's/^/unsigned char version[] = {\n/g; s/$$/};\n/g' > $@

branch.h:
	git rev-parse --abbrev-ref HEAD | tr -d '\r\n' | sed 's/master/ /g' | xxd -u -p -c 1 | sed 's/\s+/_/g' | sed 's/^/  0x/g; s/$$/,/g' | sed -z 's/^/unsigned char branch[] = {\n/g; s/$$/};\n/g' > $@

$(BIN):	obj branch.h version.h obj/main.o obj/bank_00.o obj/bank_01.o obj/bank_02.o obj/bank_03.o obj/bank_04.o obj/bank_05.o obj/bank_06.o obj/bank_07.o obj/bank_08.o obj/bank_09.o obj/bank_10.o obj/bank_11.o obj/bank_12.o obj/bank_13.o obj/bank_14.o obj/bank_15.o obj/bank_16.o obj/pxlr.sav obj/printCmd.o
	$(CC) -Wl-yt0xFC -Wl-yo4 -Wl-ya16 -Wm-yn"PXLR CAMERA" -o obj/$@ obj/main.o obj/bank_00.o obj/bank_01.o obj/bank_02.o obj/bank_03.o obj/bank_04.o obj/bank_05.o obj/bank_06.o obj/bank_07.o obj/bank_08.o obj/bank_09.o obj/bank_10.o obj/bank_11.o obj/bank_12.o obj/bank_13.o obj/bank_14.o obj/bank_15.o obj/bank_16.o obj/printCmd.o
