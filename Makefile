include Makefile.inc
.PHONY: all clean run
DIRS = src/core

all: bskernel bsos.iso

bsos.iso: bskernel iso/boot/grub/grub.cfg
	@echo Building bsos.iso...
	@cp bskernel iso/boot/bskernel
	@grub-mkrescue -d /usr/lib/grub/i386-pc/ -o $@ iso/ -- -quiet
	
bskernel:
	$(MAKE) -C kernel/
	cp kernel/bskernel .

dump: bskernel
	@objdump -M intel -D $< > $@

run:
	echo "c" | bochs -q

clean:
	@echo Cleaning...
	
	@echo Removing kernel...
	@rm -rf iso/boot/bskernel
	@rm -rf bskernel
	
	@echo Removing dump file...
	@rm -rf dump

	@echo Removing bsos.iso...
	@rm -if bsos.iso

	$(MAKE) -C kernel/ clean
