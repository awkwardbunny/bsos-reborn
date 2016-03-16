include ../Makefile.inc
C_SRC = $(wildcard *.c)
OBJ = $(C_SRC:.c=.o)
OBJ += start.o
INCL = $(wildcard include/*)

bskernel: linker.ld $(OBJ)
	@echo Building kernel...
	@$(LD) -T $< -o $@ $(OBJ)

start.o: start.s
	@echo Building start.o...
	@$(AS) $< -o $@

%.o: %.c $(INCL)
	@echo Building $@...
	@$(CC) $(CFLAGS) -c $< -I./include -o $@

clean:
	@echo Cleaning kernel...
	@rm -f bskernel
	
	@echo Removing object files...
	@rm -f *.o
