#include <system.h>
#include <multiboot.h>

void *memcpy(void *dest, const void *src, size_t count){
	uint8_t *a = dest;
	const uint8_t *b = src;
	for(size_t i = 0; i < count; i++){
		a[i] = b[i];
	}
	return dest;
}

void *memset (void *dest, uint8_t val, size_t count){
	uint8_t *a = dest;
	for(size_t i = 0; i < count; i++){
		a[i] = val;
	}
	return dest;
}

uint16_t *memsetw (uint16_t *dest, uint16_t val, size_t count){
	for(size_t i = 0; i < count; i++){
		dest[i] = val;
	}
	return dest;
}

size_t strlen(const char* str){
	size_t ret = 0;
	while ( str[ret] )
		ret++;
	return ret;
}

char* itoa(int val){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i; --i, val/=16)
		buf[i] = "0123456789abcdef"[val % 16];
	return &buf[i+1];
}

void check_bootloader_info(uint32_t magic, struct multiboot_info *mb_ptr){
	if(magic != MB_BOOTLOADER_MAGIC){
		printf("Invalid magic number: %x\n", magic);
	}

	uint32_t flags = mb_ptr->flags;

	if(CHECK_FLAG(flags, 0)){
		printf ("mem_lower = %dKB\tmem_upper = %dKB (%dMB) %x\n", mb_ptr->mem_lower, mb_ptr->mem_upper, mb_ptr->mem_upper >> 10, mb_ptr->mem_upper + 1024  << 10);
	}

	if(CHECK_FLAG(flags, 1)){
		unsigned int bd = mb_ptr->boot_device;
		printf ("boot_device = %x; ", bd);
		printf ("drive:%2x, part1:%2x, part2:%2x, part3:%2x\n", bd>>24 & 0xff, bd>>16 & 0xff, bd>>8 & 0xff, bd & 0xff );
	}

	if(CHECK_FLAG(flags, 2)){
		printf ("cmdline = %s\n", mb_ptr->cmdline);
	}

	if(CHECK_FLAG(flags, 3)){
		printf ("mods_count = %d, mods_addr = %x\n", mb_ptr->mods_count, mb_ptr->mods_addr);
		typedef struct multiboot_mod_list mmlist;
		unsigned int i;
		mmlist *mod;
		for (i = 0, mod = (mmlist *) mb_ptr->mods_addr; i < mb_ptr->mods_count; i++, mod++)
			printf (" mod_start = %x, mod_end = %x, cmdline = %s\n", (unsigned)mod->mod_start, (unsigned)mod->mod_end, (char *) mod->string);
	}

	if (CHECK_FLAG (flags, 6)){
		mb_memory_map_t *mmap;

		printf ("mmap_addr = %x, mmap_length = %x\n", mb_ptr->mmap_addr, mb_ptr->mmap_length);

		for (mmap = (mb_memory_map_t *) mb_ptr->mmap_addr;(unsigned long) mmap < mb_ptr->mmap_addr + mb_ptr->mmap_length; mmap = (mb_memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size))){
			uint64_t addr_base = mmap->addr;
			uint64_t len = mmap->len;
			uint64_t addr_end = addr_base + len;
			printf ("From: %x %x To: %x %x Type: %x\n",
				(int)(addr_base >> 32),
				(int)(addr_base & 0xffffffff),
				(int)(addr_end >> 32),
				(int)(addr_end & 0xffffffff),
				(unsigned) mmap->type);
		}
   }
}
