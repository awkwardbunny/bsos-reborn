PREFIX=i686-elf-
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

bsos.iso: kernel.bin src/iso/boot/grub/grub.cfg
	@echo Building bsos.iso...
	@cp kernel.bin src/iso/boot/kernel.bin
	@grub-mkrescue -o $@ src/iso/

kernel.o: src/kernel/main.c
	@echo Building kernel.o...
	@$(PREFIX)gcc -c src/kernel/main.c -o $@ $(CFLAGS)

boot.o: src/boot/boot.s
	@echo Building boot.o...
	@$(PREFIX)as src/boot/boot.s -o $@

kernel.bin: boot.o kernel.o src/linker.ld
	@echo Building kernel.bin...
	@$(PREFIX)gcc -T src/linker.ld -o $@ -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

clean:
	@echo Cleaning...
	@rm -rf *.o *.bin
	@rm -rf /src/iso/boot/*.bin
	@rm -i *.iso