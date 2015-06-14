#include <desc_tables.h>

struct gdt_entry gdt[5];
struct gdt_ptr gp;

extern void gdt_flush();

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = ((base >> 16) & 0xFF);
	gdt[num].base_high = ((base >> 24) & 0xFF);

	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = (limit >> 16) & 0x0F;

	gdt[num].granularity |= (gran & 0xF0);

	gdt[num].access = access;
}

void gdt_install(){
	gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
	gp.base = (uint32_t)&gdt;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Kernel
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); //User
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	gdt_flush();
}