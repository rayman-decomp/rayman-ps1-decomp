#NOTES
#hardcoded pointers:
#	the address 0x8005866C (main(), loading_794DC.c, loading_A0338.c, first_init.c)
#	swap_level (unused), START_WORLD_VIGNET, draw_sprite_gen
#	loading_tex.c (??? i can't tell)
#	(.data) loading_AA6EC.c, loading_9FB74.c, video_AA6DC.c

#see DO_BBL_COMMAND for current way of writing block_flags[mp.map[...]]
#apply MAX/MIN macros to code from before then
#is there a way to inline EOA()? (include/common/macro.h)
#rewrite some old while loops as for (or do{}while() as while), e.g. "allocate*" functions
#places, where you might use ternary instead? (search "OBJ_FLIP_X) &&")
#inline in DISPLAY_ANYSIZE_FND and do_flocons?

#renamed duplicate cd_cw, cd_read, memcpy, set_alarm in the beginning of the decomp

EXE               := slus-000.05

ASM_DIR           := asm
BUILD_DIR         := build
EXP_DIR           := expected
SRC_DIR           := src
TOOLS_DIR         := tools

BUILD_EXE         := $(BUILD_DIR)/$(EXE)

PYTHON            := python3

CROSS             := mipsel-linux-gnu-
CPP               := $(CROSS)cpp
CPP_FLAGS         := -Iinclude -I$(TOOLS_DIR)/psyq-3.0-converted/include
CC                := $(TOOLS_DIR)/gcc-2.5.7/cc1
CC_FLAGS          := -quiet -mgas -msoft-float -G0 -O2 -fno-builtin -gcoff -Wimplicit
MASPSX            := $(PYTHON) $(TOOLS_DIR)/maspsx/maspsx.py
MASPSX_FLAGS      := --macro-inc --expand-div --aspsx-version=2.08
AS                := $(CROSS)as
AS_FLAGS          := -EL -mips2 -msoft-float -no-pad-sections -Iinclude
LD                := $(CROSS)ld
LD_FLAGS          := -EL -T $(EXE).ld -T undefined_syms_auto.txt -T undefined.txt -Map $(BUILD_EXE).map

ASM_FILES         := $(wildcard $(ASM_DIR)/**.s) $(wildcard $(ASM_DIR)/**/**.s)
SRC_FILES_O2      := $(wildcard $(SRC_DIR)/**.c) $(wildcard $(SRC_DIR)/**/**.c) $(wildcard $(SRC_DIR)/**/**/**.c)
SRC_FILES_O1      := 
SRC_FILES_SCRATCH := 
SRC_FILES_O2      := $(filter-out $(SRC_FILES_O1) $(SRC_FILES_SCRATCH), $(SRC_FILES_O2))

O_ASM             := $(foreach file,$(ASM_FILES),$(BUILD_DIR)/$(file).o)
O_SRC_O2          := $(foreach file,$(SRC_FILES_O2),$(BUILD_DIR)/$(file).o)
O_SRC_O1          := $(foreach file,$(SRC_FILES_O1),$(BUILD_DIR)/$(file).o)
O_SRC_SCRATCH     := $(foreach file,$(SRC_FILES_SCRATCH),$(BUILD_DIR)/$(file).o)

default: $(BUILD_EXE) check

extract: splat dirs

splat:
	mkdir -p $(ASM_DIR)
	$(PYTHON) -m splat split $(EXE).yaml

#also creates nonmatchings directory that is not needed
dirs:
	$(foreach dir,$(shell find $(ASM_DIR) -type d) $(shell find $(SRC_DIR) -type d),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
	mkdir -p $(EXP_DIR)

$(BUILD_EXE): $(BUILD_EXE).elf
	$(CROSS)objcopy -O binary $< $@

$(BUILD_EXE).elf: $(O_ASM) $(O_SRC_O2) $(O_SRC_O1) $(O_SRC_SCRATCH)
	$(LD) $(LD_FLAGS) -o $@

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<

#see https://github.com/decompme/decomp.me/blob/45e8a9078424154a3177a4db5fa08aa930445295/backend/coreapp/compilers.py#L352
$(O_SRC_O2) : $(BUILD_DIR)/%.o : %
	$(CPP) $(CPP_FLAGS) $< | $(CC) $(CC_FLAGS) | $(MASPSX) $(MASPSX_FLAGS) | $(AS) $(AS_FLAGS) -o $@

$(O_SRC_O1) : $(BUILD_DIR)/%.o : %
	$(CPP) $(CPP_FLAGS) $< | $(CC) -quiet -mgas -msoft-float -G0 -O1 -fno-builtin -gcoff | $(MASPSX) $(MASPSX_FLAGS) | $(AS) $(AS_FLAGS) -o $@

CC_SCR := $(TOOLS_DIR)/gcc-2.5.7/cc1
$(O_SRC_SCRATCH) : $(BUILD_DIR)/%.o : %
	$(CPP) $(CPP_FLAGS) $< | $(CC_SCR) -quiet -mgas -msoft-float -G0 -O2 -fno-builtin -gcoff | $(MASPSX) $(MASPSX_FLAGS) | $(AS) $(AS_FLAGS) -o $@

check:
	sha1sum --check $(EXE).sha1

clean:
	rm -rf $(ASM_DIR) $(BUILD_DIR) $(EXE).ld undefined_funcs_auto.txt undefined_syms_auto.txt