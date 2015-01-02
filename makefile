CSRC=$(wildcard src/kernel/*.c src/kernel/drivers/*.c)
CHDR=$(wildcard src/kernel/*.h src/kernel/drivers/*.h)
OBJ=${CSRC:.c=.o}

PREFIX=i686-elf-
AS=$(PREFIX)as
LD=$(PREFIX)ld
GCC=$(PREFIX)gcc

CFLAGS=-std=gnu99 -ffreestanding
CFLAGS_KERNO=$(CFLAGS) -O2 -Wall -Wextra
CFLAG_KERNEL=-T src/linker.ld -ffreestanding -O2 -nostdlib -lgcc

all: bsos.iso

boot.o: src/boot/boot.s
	@echo Building boot.o...
	@$(AS) src/boot/boot.s -o src/boot/$@

src/kernel/kernel.o: src/kernel/kernel.c
	@echo Building kernel.o...
	@$(GCC) -c $^ -o $@ $(CFLAGS_KERNO)

%.o: %.c ${CHDR}
	@$(GCC) -c $< -o $@ $(CFLAGS)

src/kernel.bin: src/boot/boot.o ${OBJ}
	@echo Building kernel.bin...
	@$(GCC) -o $@ $^ $(CFLAG_KERNEL)

bsos.iso: src/kernel.bin src/iso/boot/grub/grub.cfg
	@echo Building bsos.iso...
	@cp src/kernel.bin src/iso/boot/kernel.bin
	@grub-mkrescue -o $@ src/iso/

clean:
	@echo Cleaning...
	@rm -rf src/iso/boot/kernel.bin
	@rm -rf src/kernel.bin
	@rm -rf src/boot/boot.o
	@rm -rf ${OBJ}
	@rm -if bsos.iso