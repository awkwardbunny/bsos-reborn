BSOS - Reborn
===========
A better version development of the [original 'BSOS' project](https://github.com/aplabs/bsos).

One big change so far is that, instead of writing my own bootloader, I will be using GRUB and multiboot header.  
It's also built with a i686-elf cross-compiler built with instructions [here](http://wiki.osdev.org/GCC_Cross-Compiler) on the OSDEV wiki. The toolchain should be place under $HOME/opt/cross.

###Building
Below will make a kernel file and an bootable .iso file.
```
git clone https://github.com/awkwardbunny/bsos-reborn/
cd bsos-reborn
. ./setenv.sh
make
```

###Running
To run, since the Bochs emulator is installed and configured with bochsrc file, just type in 'bochs' in the project root.  
I have compiled bochs from source with the debugging option enabled, which is why I have a 'run' target in makefile  
```
bochs  

or

make run
```

####Resources
* The [OSDev Wiki](http://wiki.osdev.org/) has many tutorials and lots more resources.
* [Bran's Kernel Dev tutorial](http://www.osdever.net/bkerndev/Docs/title.htm)
* [Building target specific cross-comiler toolchain](http://wiki.osdev.org/GCC_Cross-Compiler)
* [Keyboard Scancodes](http://flint.cs.yale.edu/cs422/doc/art-of-asm/pdf/APNDXC.PDF)
* [BrokenThorn Entertainment](http://www.brokenthorn.com/Resources/) tutorial
* [Basic Kernel in C](http://www.cs.vu.nl/~herbertb/misc/basickernel.pdf)
* [Bochs](http://bochs.sourceforge.net/) Emulator
