PREFIX=i686-elf-

AS = $(PREFIX)as

LD = $(PREFIX)ld
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

GCC = $(PREFIX)gcc
CFLAGS = -std=gnu99 -ffreestanding -finline-functions -nostdinc -fno-builtin -O2 -m32