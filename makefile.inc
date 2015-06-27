PREFIX=i686-elf-

AS = $(PREFIX)as

LD = $(PREFIX)ld
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

GCC = $(PREFIX)gcc
CFLAGS = -ffreestanding -nostdinc -std=gnu99 -m32 -finline-functions -fno-builtin -fstrength-reduce -Wall -Wextra
# -Wno-unused-parameter # Last flags is for now
# -O2 #must be removed to manually trip page fault for now