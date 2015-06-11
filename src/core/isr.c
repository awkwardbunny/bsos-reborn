#include "desc_tables.h"
#include "vga.h"

char *exception_messages[] = {
	"division by zero",
	"debug",
	"non-maskable interrupt",
	"breakpoint",
	"detected overflow",
	"out-of-bounds",
	"invalid opcode",
	"no coprocessor",
	"double fault",
	"coprocessor segment overrun",
	"bad TSS",
	"segment not present",
	"stack fault",
	"general protection fault",
	"page fault",
	"unknown interrupt",
	"coprocessor fault",
	"alignment check",
	"machine check",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved"
};

char* itoa(int val){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i; --i, val/=16)
		buf[i] = "0123456789abcdef"[val % 16];
	return &buf[i+1];
}

void isr_handler(struct registers regs){
	puts("Received interrupt: ");
	if(regs.int_no < 32){
		puts(exception_messages[regs.int_no]);
		puts(" exception. System halted.\n");
	}else{
		puts("UNKNOWN!! ");
		puts(itoa(regs.int_no));
		puts("\n");
	}
}