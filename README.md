BSOS - Reborn
===========
A better version development of the [original 'BSOS' project](https://github.com/aplabs/bsos).

One big change so far is that, instead of writing my own bootloader, I will be using GRUB and multiboot header.

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
