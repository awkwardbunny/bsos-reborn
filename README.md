BSOS - Reborn
===========
A better version development of the [original 'BSOS' project](https://github.com/aplabs/bsos).

One big change so far is that, instead of writing my own bootloader, I will be using GRUB and multiboot header.  
The cross compiler used is from Richard Hull's [repo](https://github.com/rm-hull/i686-elf), built with instructions here: [http://wiki.osdev.org/GCC_Cross-Compiler](http://wiki.osdev.org/GCC_Cross-Compiler).  
I claim no intellectual property over said materials.

###Building
```
git clone https://github.com/awkwardbunny/bsos-reborn/
cd bsos-reborn
. ./setenv.sh
make
```

###Running
With the Bochs emulator installed and configured with bochsrc file,
```
bochs
```

####Resources
Built with instructions from the osdev wiki [bare bones tutorial](http://wiki.osdev.org/Bare_Bones)
GCC [i686-elf Cross-Compiler](https://github.com/rm-hull/i686-elf)
