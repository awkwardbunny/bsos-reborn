include makefile.inc
.PHONY: all clean core run dump
DIRS = src/core

all: bsos.iso dump

bsos.iso: kernel iso/boot/grub/grub.cfg
	@echo Building bsos.iso...
	@cp kernel iso/boot/kernel
	@grub-mkrescue -o $@ iso/
	
kernel: src/start.o src/linker.ld src/kmain.o core
	@echo Building kernel...
	@$(LD) -T src/linker.ld -o $@ src/core/*.o src/*.o

core:
	$(MAKE) -C src/core $(MFLAGS)

src/start.o: src/start.s
	@echo Building start.o...
	@$(AS) src/start.s -o $@

src/kmain.o: src/kmain.c $(wildcard src/include/*)
	@echo Building kmain.o...
	@$(GCC) $(CFLAGS) -c $< -I./src/include -o $@

dump:
	@objdump -M intel -D kernel > dump

run:
	@./run

clean:
	@echo Cleaning...
	
	@echo Removing kernel...
	@rm -rf iso/boot/kernel
	@rm -rf kernel
	
	@echo Removing dump file...
	@rm -rf dump

	@echo Removing object files...
	@rm -rf src/*.o

	@echo Removing bsos.iso...
	@rm -if bsos.iso
	@for d in $(DIRS); do ($(MAKE) -C $$d clean); done