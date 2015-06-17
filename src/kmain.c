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

int kernel_main(struct multiboot_info *mb_ptr)
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();

	asm volatile ("sti"); 

	init_video();
	timer_install();
	//timer_wait(10);
	kbd_install();

	printf("Booted to KERNEL!\n");
	printf("Booted from %s\n", mb_ptr->boot_loader_name);
	printf("with parameter: %s\n", mb_ptr->cmdline);

	setcolor(0x02);
	printf("Testing multiboot info:\n");
	printf("Flags: %x\n", mb_ptr->flags);
	printf("mem_lower: %dkB\tmem_upper: %dkB", mb_ptr->mem_lower, mb_ptr->mem_upper);
	printf(" (%dMB)\n", (mb_ptr->mem_upper)/1024);
	printf("boot_device = %x\n", mb_ptr->boot_device);
	printf("%d mods at %x\n", mb_ptr->mods_count, mb_ptr->mods_addr);
	printf("mmap: %d at %x\n", mb_ptr->mmap_length, mb_ptr->mmap_addr);
	printf("%d drives at %x\n", mb_ptr->drives_length, mb_ptr->drives_addr);
	printf("config: %x\n", mb_ptr->config_table);
	printf("VBE Control: %x\t", mb_ptr->vbe_control_info);
	printf("VBE Mode Info: %x\t", mb_ptr->vbe_mode_info);
	printf("VBE Mode: %x\n", mb_ptr->vbe_mode);
	printf("VBE seg: %x\t", mb_ptr->vbe_interface_seg);
	printf("VBE off: %x\t", mb_ptr->vbe_interface_off);
	printf("VBE len: %x\n", mb_ptr->vbe_interface_len);

	setcolor(COLOR_ATTR(LGRAY, BLACK));

	for(;;);
	return 0;
}