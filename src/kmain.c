#if defined(__linux__)
#error "Please compile with i386-elf cross compiler!"
#endif
 
#if !defined(__i386__)
#error "Please compile with i386-elf compiler"
#endif

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#else
/* stdbool */
#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined 1
#endif

#include "system.h"
#include "multiboot.h"
#include "vga.h"
#include "desc_tables.h"
#include "timer.h"
#include "keyboard.h"

int kernel_main(struct multiboot *mb_ptr)
{
	gdt_install();
	idt_install();
	irq_install();

	asm volatile ("sti"); 

	timer_install();
	//timer_wait(10);
	kbd_install();

	init_video();
	puts("Hello, kernel World!\n");

	for(;;);
	return 0;
}