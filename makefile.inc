PREFIX=i686-elf-

AS = $(PREFIX)as

LD = $(PREFIX)ld
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

GCC = $(PREFIX)gcc
CFLAGS = -ffreestanding -O2 -nostdinc -std=gnu99 -m32 -finline-functions -fno-builtin -fstrength-reduce -Wall -Wextra -Wno-unused-parameter # Last flags is for now