include ../../makefile.inc
.PHONY: all clean core

C_SRC = $(wildcard *.c)
OBJ = $(C_SRC:.c=.o)

all: $(OBJ)

%.o: %.c
	@echo Building $@...
	@$(GCC) $(CFLAGS) -I../include -c -o $@ $<

clean:
	@echo Removing core object files...
	@rm -f *.o