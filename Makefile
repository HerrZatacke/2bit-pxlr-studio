SHELL := /bin/bash

# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"

GBDK_HOME = $(GBDK_FOLDER)/
#GBCPU = gbz80

#GBDK_HOME = ../../../gbdk-2020/build/gbdk/
GBCPU = sm83

LCC = $(GBDK_HOME)bin/lcc
PNG2ASSET = $(GBDK_HOME)bin/png2asset

# Set platforms to build here, spaced separated. (These are in the separate Makefile.targets)
# They can also be built/cleaned individually: "make gg" and "make gg-clean"
# Possible are: gb gbc pocket sms gg
#TARGETS = gb gbc pocket sms gg
TARGETS = gb

#LIBRARIES = -Wl-llib/$(PORT)/hUGEDriver.lib
LIBRARIES =

# Configure platform specific LCC flags here:
LCCFLAGS_gb      = $(LIBRARIES) -Wl-yt0xFC -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_pocket  = $(LIBRARIES) -Wl-yt0xFC -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_gbc     = $(LIBRARIES) -Wl-yt0xFC -Wm-yn"$(PROJECTNAME)"
LCCFLAGS_sms     =
LCCFLAGS_gg      =

LCCFLAGS += $(LCCFLAGS_$(EXT)) -Wm-yS # This adds the current platform specific LCC Flags

LCCFLAGS += -Wl-j -Wm-yoA -Wm-ya16 -autobank -Wb-ext=.rel
# LCCFLAGS += -debug # Uncomment to enable debug output
# LCCFLAGS += -v     # Uncomment for lcc verbose output

CFLAGS = -Iinclude -Iinclude/$(PORT) -Iinclude/$(PLAT) -I$(RESDIR) -Iobj/$(PLAT)

# You can set the name of the ROM file here
PROJECTNAME = pxlr

# EXT?=gb # Only sets extension to default (game boy .gb) if not populated
SRCDIR      = src
SRCPORT     = src/$(PORT)
SRCPLAT     = src/$(PLAT)
OBJDIR      = obj/$(EXT)
RESDIR      = res
BINDIR      = build/$(EXT)
MKDIRS      = $(OBJDIR) $(BINDIR) include/generated # See bottom of Makefile for directory auto-creation

BINS	    = $(OBJDIR)/$(PROJECTNAME).$(EXT)

VGM_RES	    = $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/audio/$(PLAT)/sounds/*.vgm)))
FX_RES	    = $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/audio/$(PLAT)/sounds/*.sav)))
UGE_RES     = $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/audio/$(PLAT)/music/*.uge)))
WAV_RES     = $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/audio/$(PLAT)/waveforms/*.wav)))

SPR_RES     = $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/gfx/$(PLAT)/sprites/*.png)))
BKG_RES     = $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/gfx/$(PLAT)/backgrounds/*.png)))

CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(SRCPLAT),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(SRCPORT),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/audio/$(PLAT)/*.c))) $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/menus/*.c))) $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/overlays/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s))) $(foreach dir,$(SRCPLAT),$(notdir $(wildcard $(dir)/*.s))) $(foreach dir,$(SRCPORT),$(notdir $(wildcard $(dir)/*.s)))

OBJS        = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)
RESOBJ      = $(VGM_RES:%.vgm=$(OBJDIR)/%.o) $(WAV_RES:%.wav=$(OBJDIR)/%.o) $(FX_RES:%.sav=$(OBJDIR)/%.o) $(UGE_RES:%.uge=$(OBJDIR)/%.o) $(SPR_RES:%.png=$(OBJDIR)/%.o) $(BKG_RES:%.png=$(OBJDIR)/%.o)

DEPENDANT   = $(CSOURCES:%.c=$(OBJDIR)/%.o)

# Builds all targets sequentially
all: include/generated/version.h include/generated/branch.h $(TARGETS) build/gb/pxlr.sav

# Dependencies
DEPS = $(DEPENDANT:%.o=%.d)

-include $(DEPS)

.SECONDEXPANSION:
$(OBJDIR)/%.c:	$(RESDIR)/audio/$(PLAT)/sounds/%.vgm $$(wildcard $(RESDIR)/audio/$(PLAT)/sounds/%.vgm.meta)
	python utils/vgm2data.py -5 -w -3 -d 4 -b 255 `cat <$<.meta 2>/dev/null` -o $@ $<

.SECONDEXPANSION:
$(OBJDIR)/%.c:	$(RESDIR)/audio/$(PLAT)/sounds/%.sav $$(wildcard $(RESDIR)/audio/$(PLAT)/sounds/%.sav.meta)
	python utils/fxhammer2data.py -d 4 -c -b 255 `cat <$<.meta 2>/dev/null` -o $@ $<

$(OBJDIR)/%.c:	$(RESDIR)/audio/$(PLAT)/music/%.uge
	utils/uge2source $< -b 255 $(basename $(notdir $<)) $@

$(OBJDIR)/%.c:	$(RESDIR)/audio/$(PLAT)/waveforms/%.wav
	python utils/wav2data.py -b 255 -o $@ $<

$(OBJDIR)/%.o:	$(RESDIR)/audio/$(PLAT)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<


.SECONDEXPANSION:
$(OBJDIR)/%.c:	$(RESDIR)/gfx/$(PLAT)/sprites/%.png $$(wildcard $(RESDIR)/gfx/$(PLAT)/sprites/%.png.meta)
	$(PNG2ASSET) $< -c $@ `cat <$<.meta 2>/dev/null` -spr8x16 -b 255

.SECONDEXPANSION:
$(OBJDIR)/%.c:	$(RESDIR)/gfx/$(PLAT)/backgrounds/%.png $$(wildcard $(RESDIR)/gfx/$(PLAT)/backgrounds/%.png.meta)
	$(PNG2ASSET) $< -c $@ -map `cat <$<.meta 2>/dev/null` -b 255


$(OBJDIR)/%.o:	$(OBJDIR)/%.c
	$(LCC) $(CFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) -Wf-MMD $(CFLAGS) -c -o $@ $<


# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) -Wf-MMD $(CFLAGS) $(filter -Wf-ba%, $(subst .d,-Wf-ba,$(suffix $(<:%.c=%)))) -c -o $@ $<

# Compile .c files in "src/menus/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/menus/%.c
	$(LCC) -Wf-MMD $(CFLAGS) $(filter -Wf-ba%, $(subst .d,-Wf-ba,$(suffix $(<:%.c=%)))) -c -o $@ $<

# Compile .c files in "src/overlays/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/overlays/%.c
	$(LCC) -Wf-MMD $(CFLAGS) $(filter -Wf-ba%, $(subst .d,-Wf-ba,$(suffix $(<:%.c=%)))) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(CFLAGS) -c -o $@ $<


# Compile .c files in "src/<platform>/" to .o object files
$(OBJDIR)/%.o:	$(SRCPLAT)/%.c
	$(LCC) -Wf-MMD $(CFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/<platform>/" to .o object files
$(OBJDIR)/%.o:	$(SRCPLAT)/%.s
	$(LCC) $(CFLAGS) -c -o $@ $<


# Compile .c files in "src/<target>/" to .o object files
$(OBJDIR)/%.o:	$(SRCPORT)/%.c
	$(LCC) -Wf-MMD $(CFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/<target>/" to .o object files
$(OBJDIR)/%.o:	$(SRCPORT)/%.s
	$(LCC) $(CFLAGS) -c -o $@ $<


# Link the compiled object files into a .gb ROM file
$(BINS):	$(RESOBJ) $(OBJS)
	$(LCC) $(LCCFLAGS) $(CFLAGS) -o $(BINDIR)/$(PROJECTNAME).$(EXT) $^

include/generated/version.h: version
	tr -d '\r\n ' < $< | xxd -u -p -c 1 | sed 's/\s+/_/g' | sed 's/^/  0x/g; s/$$/,/g' | sed -z 's/^/const uint8_t version[] = {\n/g; s/$$/};\n/g' > $@

include/generated/branch.h:
	git rev-parse --abbrev-ref HEAD | tr -d '\r\n' | sed 's/master/ /g' | xxd -u -p -c 1 | sed 's/\s+/_/g' | sed 's/^/  0x/g; s/$$/,/g' | sed -z 's/^/const uint8_t branch[] = {\n/g; s/$$/};\n/g' > $@

build/gb/pxlr.sav:
	cp assets/pxlr.sav build/gb/pxlr.sav

clean:
	@echo Cleaning
	@for target in $(TARGETS); do \
		$(MAKE) $$target-clean; \
	done

# Include available build targets
include Makefile.targets


# create necessary directories after Makefile is parsed but before build
# info prevents the command from being pasted into the makefile
ifneq ($(strip $(EXT)),)           # Only make the directories if EXT has been set by a target
$(info $(shell mkdir -p $(MKDIRS)))
endif
