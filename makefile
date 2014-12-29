PREFIX=i686-elf-
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: boot.o kernel.o boot.o kernel.bin bsos.iso

kernel.o: kernel/kernel.c
	@echo Building kernel.o...
	@$(PREFIX)gcc -c kernel/kernel.c -o kernel.o $(CFLAGS)

boot.o: boot/boot.s
	@echo Building boot.o...
	@$(PREFIX)as boot/boot.s -o boot.o

kernel.bin: boot.o kernel.o
	@echo Building kernel.bin...
	@$(PREFIX)gcc -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

bsos.iso: kernel.bin
	@echo Building bsos.iso...
	@cp kernel.bin iso/boot/kernel.bin
	@grub-mkrescue -o bsos.iso iso/

clean:
	@echo Cleaning...
	@rm -rf *.o *.bin iso/boot/*.bin *.iso