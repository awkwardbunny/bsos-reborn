#if defined(__linux__)
#error "Please compile with i386-elf cross compiler!"
#endif
 
#if !defined(__i386__)
#error "Please compile with i386-elf compiler!"
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

#include <system.h>
#include <multiboot.h>
#include <vga.h>
#include <desc_tables.h>
#include <timer.h>
#include <keyboard.h>
#include <memory.h>

int kernel_main(uint32_t magic, mb_info_t *mb_ptr)
{
	init_video();

	setcolor(0x02);
	check_bootloader_info(magic, mb_ptr);
	setcolor(0x07);

	asm volatile("cli");
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	asm volatile("sti");

	timer_install();
	//timer_wait(10);
	kbd_install();

	printf("Booted to KERNEL!\n");

	for(;;);
	return 0;
}