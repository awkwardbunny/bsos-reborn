include Makefile.inc
.PHONY: all clean run bskernel

C_SRC = $(wildcard kernel/*.c)
OBJ = $(C_SRC:.c=.o)
OBJ += kernel/start.o
INCL = $(wildcard kernel/include/*)

all: bskernel bsos.iso

bsos.iso: bskernel iso/boot/grub/grub.cfg
	@echo Building bsos.iso...
	@cp bskernel iso/boot/bskernel
	@grub-mkrescue -d /usr/lib/grub/i386-pc/ -o $@ iso/ -- -quiet
	
bskernel: kernel/linker.ld $(OBJ)
	@echo Building kernel...
	@$(LD) -T $< -o $@ $(OBJ)

dump: bskernel
	@objdump -M intel -D $< > $@

run:
	(echo "c" && cat) | bochs -q

clean:
	@echo Cleaning...
	
	@echo Removing kernel...
	@rm -rf iso/boot/bskernel
	@rm -rf bskernel
	
	@echo Removing dump file...
	@rm -rf dump
	
	@echo Removing object files...
	@rm -f kernel/*.o

	@echo Removing bsos.iso...
	@rm -if bsos.iso

kernel/start.o: kernel/start.s
	@echo Building start.o...
	@$(AS) $< -o $@

%.o: %.c $(INCL)
	@echo Building $@...
	@$(CC) $(CFLAGS) -c $< -I./kernel/include -o $@
