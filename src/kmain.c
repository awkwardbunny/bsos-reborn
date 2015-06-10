#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
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
#include "vga.h"
#include "desc_tables.h"
#include "timer.h"
#include "keyboard.h"

int kernel_main()
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

	

	//IDT and ISR test
	//asm volatile ("int $0x3");
	//asm volatile ("int $0x4");

	for(;;);
	return 0;
}