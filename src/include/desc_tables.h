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

/* ISRs */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// Backwards order of which were pushed onto the stack in
// ISR and isr_common routines
struct registers{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
}__attribute__((packed));

void irq_install();
void irq_install_handler(int irq, void (*handler)(struct registers regs));
void irq_uninstall_handler(int irq);

#endif