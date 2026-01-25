> [!NOTE]
> The port repo has been moved to [rayman-decomp/rayman-ps1-decomp](https://github.com/rayman-decomp/rayman-ps1-decomp/tree/port_clean) as of January 2026.


# rayman-ps1-decomp
Please help matching the remaining [~50 nonmatching non-psyq functions](https://docs.google.com/spreadsheets/d/1vJuS9sQnzeYvZqrR-QtGGEMYePni6XKZGVvfAUoAtjU)!

WIP matching decompilation of [Rayman on the PS1](http://redump.org/disc/8326/). We had symbols from [Rayman Classic](https://raymanpc.com/wiki/en/Rayman_Classic). Unfortunately, I worked rather messy (code style, etc.).  
This repo does not come with any of the game's assets.

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

## Thanks
Tools (among others): Authors of [splat](https://github.com/ethteck/splat), [m2ctx](https://github.com/ethteck/m2ctx), [m2c](https://github.com/matt-kempster/m2c), [maspsx](https://github.com/mkst/maspsx), [asm-differ](https://github.com/simonlindholm/asm-differ), [decomp-permuter](https://github.com/simonlindholm/decomp-permuter), [decomp.me](https://github.com/decompme/decomp.me), [pcsx-redux](https://github.com/grumpycoders/pcsx-redux)  
[mkst:](https://github.com/mkst) For helping us when we had questions.  
[RayCarrot:](https://github.com/RayCarrot) A lot of labelling in ghidra, projects used as resources/game documentation.  
[Falcury:](https://github.com/Falcury) Also looking into technical stuff (PC version).  
[Mc-muffin:](https://github.com/Mc-muffin) Helping match a bunch of functions (see decomp.me links)  
[sotn-decomp:](https://github.com/xeeynamo/sotn-decomp) Big brother decomp to look up to.
