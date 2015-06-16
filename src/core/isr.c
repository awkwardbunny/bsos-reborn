#include <desc_tables.h>
#include <vga.h>

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

void isr_handler(struct registers regs){
	puts("Received interrupt: ");
	if(regs.int_no < 32){
		puts(exception_messages[regs.int_no]);
		puts(" exception. System halted.\n");
	}
}