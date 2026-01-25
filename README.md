# Rayman PS1 Decompilation

This is a WIP matching decompilation of [the PlayStation version of Rayman 1](http://redump.org/disc/8326/) created by [fuerchter](https://github.com/fuerchter). It uses the symbols from the android version of [Rayman Classic](https://raymanpc.com/wiki/en/Rayman_Classic) where possible, with custom names being prefixed with `PS1_`. This repo does not come with any of the game's assets.

## Build instructions for ubuntu (24.04.1 LTS) and WSL with splat:
```
git clone --recursive https://github.com/fuerchter/rayman-ps1-decomp
```
Add SLUS-000.05 `sha1 4ac1789e118933762cd0ebcb9a970f63dfe2c72f` to project root  
Get [gcc-2.5.7.tar.gz](https://github.com/decompals/old-gcc/releases), extract and add it to the tools dir (extracted path of cc1 e.g.: tools/gcc-2.5.7/cc1)
```
sudo apt install python3 python3-pip binutils-mipsel-linux-gnu cpp-mipsel-linux-gnu
pip install -r requirements.txt
make -f mk-splat.mk extract
make -f mk-splat.mk
```
sha1sum should print OK

## Remaining non-matching functions
Any help with these is greatly appreciated! Feel free to create a PR or open an issue if you get any of them to match. 

| File                        | Function                         | Address | Link                            | % matching |
|-----------------------------|----------------------------------|-------------|---------------------------------|------------|
| src/card.c                  | PS1_WriteSave                    | 8016AC64    | https://decomp.me/scratch/hG4wh | 99.29%     |
| src/save.c                  | restoreGameState                 | 80163C84    | https://decomp.me/scratch/F5Ked | 98.86%     |
| src/sound.c                 | PlaySnd                          | 80166E94    | https://decomp.me/scratch/KzhV8 | 97.51%     |
| src/video.c                 | PS1_PlayVideoFile                | 80132A44    | https://decomp.me/scratch/CMLNM | 96.47%     |
| src/collision/block_6E5E0.c | CALC_MOV_ON_BLOC                 | 80193A3C    | https://decomp.me/scratch/dYt2F | 94.69%     |
| src/draw/draw_14FF4.c       | DISPLAY_ALL_OBJECTS              | 8013C2BC    | https://decomp.me/scratch/0fY1o | 99.58%     |
| src/draw/draw_548CC.c       | Display_and_free_luciole         | 80179218    | https://decomp.me/scratch/4ai6p | 94.73%     |
| src/draw/fond_10B3C.c       | PS1_LoadFondDataAndPalettes      | 801356E0    | https://decomp.me/scratch/Qh0Tt | 98.41%     |
| src/draw/fond_10B3C.c       | PS1_LoadFond                     | 80135930    | https://decomp.me/scratch/l547t | 97.14%     |
| src/draw/fond_10B3C.c       | FUN_80135d5c                     | 80135D5C    | https://decomp.me/scratch/gNtGz | 88.67%     |
| src/draw/fond_10B3C.c       | FUN_80136340                     | 80136340    | https://decomp.me/scratch/2zVov | 99.04%     |
| src/draw/fond_10B3C.c       | FUN_801366ac                     | 801366AC    | https://decomp.me/scratch/kHz3p | 97.66%     |
| src/draw/fond_10B3C.c       | PS1_DisplayFondSprites           | 8013733C    | https://decomp.me/scratch/bRw9c | 99.05%     |
| src/draw/text_18118.c       | display_text                     | 8013DA5C    | https://decomp.me/scratch/HLz85 | 99.25%     |
| src/menu/menu_82008.c       | FUN_801a6808                     | 801A6808    | https://decomp.me/scratch/U35Nx | 96.68%     |
| src/obj/bb1.c               | DO_BBMONT2_COMMAND               | 8017EAA4    | https://decomp.me/scratch/07j9E | 89.38%     |
| src/obj/dark_phase2.c       | allocate_DARK2_SORT              | 8019C464    | https://decomp.me/scratch/GLrrh | 99.81%     |
| src/obj/eyes_4BC40.c        | DO_ROLL_EYES                     | 80170440    | https://decomp.me/scratch/NR6Iv | 99.05%     |
| src/obj/mite.c              | DO_MIT_ATTAK                     | 8016F4FC    | https://decomp.me/scratch/mitn7 | 98.67%     |
| src/obj/spider_plafond.c    | DO_DARD_PLAFOND_ALWAYS           | 80178938    | https://decomp.me/scratch/SonmS | 92.47%     |
| src/obj/ufo_idc.c           | DO_MOVING_WITH_INDICATOR_COMMAND | 80199230    | https://decomp.me/scratch/u9HGf | 93.81%     |

## Credits
- [fuerchter:](https://github.com/fuerchter) Original creator of the decomp, matching the majority of the functions.
- Tools (among others): Authors of [splat](https://github.com/ethteck/splat), [m2ctx](https://github.com/ethteck/m2ctx), [m2c](https://github.com/matt-kempster/m2c), [maspsx](https://github.com/mkst/maspsx), [asm-differ](https://github.com/simonlindholm/asm-differ), [decomp-permuter](https://github.com/simonlindholm/decomp-permuter), [decomp.me](https://github.com/decompme/decomp.me), [pcsx-redux](https://github.com/grumpycoders/pcsx-redux).
- [mkst:](https://github.com/mkst) For helping us when we had questions.
- [RayCarrot:](https://github.com/RayCarrot) A lot of labelling in Ghidra, projects used as resources/game documentation.
- [Falcury:](https://github.com/Falcury) Also looking into technical stuff (PC version).
- [Mc-muffin:](https://github.com/Mc-muffin) Helping match a bunch of functions (see decomp.me links).
- [sotn-decomp:](https://github.com/xeeynamo/sotn-decomp) Big brother decomp to look up to.
