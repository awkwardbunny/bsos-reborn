PREFIX=x86_64-elf-
AS = $(PREFIX)as
LD = $(PREFIX)ld
CC = $(PREFIX)gcc
LDFLAGS = -m elf_i386
CFLAGS = -ffreestanding -nostdinc -std=gnu99 -m32 -finline-functions -fno-builtin -fstrength-reduce -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function # Last 3 flags is for now
# -O2 #must be removed to manually trip page fault for now
