include makefile.inc
.PHONY: all clean core run
DIRS = src/core

all: bsos.iso

bsos.iso: kernel iso/boot/grub/grub.cfg
	@echo Building bsos.iso...
	@cp kernel iso/boot/kernel
	@grub-mkrescue -o $@ iso/
	
kernel: src/start.o src/linker.ld src/kmain.o core
	@echo Building kernel...
	@$(LD) -T src/linker.ld -o $@ src/core/*.o src/*.o
#-ffreestanding -O2 -nostdlib -lgcc #not sure if I need this?

core:
	@cd src/core; $(MAKE) $(MFLAGS)

src/start.o: src/start.s
	@echo Building start.o...
	@$(AS) src/start.s -o $@

src/kmain.o: src/kmain.c
	@echo Building kmain.o...
	@$(GCC) $(CFLAGS) -c $^ -I./src/include -o $@
#-O2 -Wall -Wextra #this too?
#-Wall -m32 -O0 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin #what about this?

run:
	@./run

clean:
	@echo Cleaning...
	@rm -rf iso/boot/kernel
	@rm -rf kernel
	@rm -rf src/*.o
	@rm -if bsos.iso
	@for d in $(DIRS); do (cd $$d; $(MAKE) clean); done