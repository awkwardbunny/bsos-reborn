#ifndef DESC_TABLES_H
#define DESC_TABLES_H

#include <system.h>

/* GDT Stuff */
struct gdt_entry{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
}__attribute__((packed));

struct gdt_ptr{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

void gdt_install();
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);


/* IDT Stuff */
struct idt_entry{
	uint16_t base_low;
	uint16_t sel;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_high;
}__attribute__((packed));

struct idt_ptr{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

void idt_install();
void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);

// Backwards order of which were pushed onto the stack in
// ISR and isr_common routines
struct registers{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
}__attribute__((packed));

void isrs_install();
void isrs_install_handler(int isrs, void (*handler)(struct registers regs));
void isrs_uninstall_handler(int isrs);

void irq_install();
void irq_install_handler(int irq, void (*handler)(struct registers regs));
void irq_uninstall_handler(int irq);

#endif