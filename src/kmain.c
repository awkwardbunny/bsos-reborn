#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "vga.h"
#include "system.h"
#include "desc_tables.h"
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

int kernel_main()
{
	gdt_install();
	idt_install();

	init_video();
	puts("Hello, kernel World!\n");

	//color ans scroll() test
	setcolor(0x12);
	for(int i = 0; i < 26; i++)
		puts("Hello, kernel World!\n");

	setcolor(0x34);
	for(int i = 0; i < 3; i++)
		puts("Hello, kernel World!\n");

	//IDT and ISR test
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");

	for(;;);
	return 0;
}