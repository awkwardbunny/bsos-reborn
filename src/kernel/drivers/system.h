#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stddef.h>

uint8_t *memcpy (uint8_t *dest, uint8_t *src, size_t count);
uint8_t *memset (uint8_t *dest, uint8_t val, size_t count);
uint16_t *memsetw (uint16_t *dest, uint16_t val, size_t count);
size_t strlen (const char *str);

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

#endif