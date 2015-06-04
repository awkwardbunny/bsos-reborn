#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "drivers/vga.h"
#include "drivers/system.h"

 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

int kernel_main()
{
	gdt_install();
	init_video();
	puts("Hello, kernel World!\n");

	setcolor(0x12);
	for(int i = 0; i < 26; i++)
		puts("Hello, kernel World!\n");

	setcolor(0x34);
	for(int i = 0; i < 3; i++)
		puts("Hello, kernel World!\n");

	for(;;);
	return 0;
}