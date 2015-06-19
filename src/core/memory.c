#include <system.h>
#include <memory.h>

uint32_t placement_addr = 0;

uint32_t kmalloc(uint32_t size){
	uint32_t tmp = placement_addr;
	placement_addr += size;
	return tmp;
}

uint32_t kmalloc_a(uint32_t size){
	
	placement_addr &= 0xFFFFF000;
	placement_addr += 0x1000;

	return kmalloc(size);
}

uint32_t kmalloc_p(uint32_t size, uint32_t *phys){
	uint32_t res = kmalloc(size);
	*phys = res;
	return res;
}

uint32_t kmalloc_ap(uint32_t size, uint32_t *phys){
	uint32_t res = kmalloc_a(size);
	*phys = res;
	return res;
}