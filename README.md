BSOS - Reborn
===========
A better version development of the [original 'BSOS' project](https://github.com/aplabs/bsos).

One big change so far is that, instead of writing my own bootloader, I will be using GRUB and multiboot header.  
It's also built with a i686-elf cross-compiler built with instructions [here](http://wiki.osdev.org/GCC_Cross-Compiler) on the OSDEV wiki. The toolchain should be place under $HOME/opt/cross.

###Building
```
git clone https://github.com/awkwardbunny/bsos-reborn/
cd bsos-reborn
. ./setenv.sh
make
```

###Running
Since the bochsrc configuration file is set for 'sdl' make sure bochs-sdl is installed. Since the Bochs emulator installed and configured with bochsrc file,
```
bochs
```

####Resources
Built with instructions from the osdev wiki [bare bones tutorial](http://wiki.osdev.org/Bare_Bones)
GCC [i686-elf Cross-Compiler](https://github.com/rm-hull/i686-elf)
