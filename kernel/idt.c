#include <desc_tables.h>

struct idt_entry idt[256];
struct idt_ptr ip;

extern void idt_flush();

void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags){
	idt[num].base_low = (base & 0xFFFF);
	idt[num].base_high = ((base >> 16) & 0xFFFF);

	idt[num].sel = sel;
	idt[num].zero = 0;

	idt[num].flags = flags;
}

void idt_install(){
	ip.limit = (sizeof(struct idt_entry) * 256) - 1;
	ip.base = (uint32_t)&idt;
	memset(&idt, 0, sizeof(struct idt_entry) * 256);

	idt_flush();
}