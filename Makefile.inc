PREFIX=i686-elf-
AS = $(PREFIX)as
LD = $(PREFIX)ld
CC = $(PREFIX)gcc
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc
CFLAGS = -ffreestanding -nostdinc -std=gnu99 -m32 -finline-functions -fno-builtin -fstrength-reduce -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function # Last 3 flags is for now
# -O2 #must be removed to manually trip page fault for now
