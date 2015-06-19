#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <system.h>

#define MB_FLAG_MEM 0x001
#define MB_FLAG_DEV 0x002
#define MB_FLAG_CMDL 0x004
#define MB_FLAG_MODS 0x008
#define MB_FLAG_AOUT 0x010
#define MB_FLAG_ELF 0x020
#define MB_FLAG_MMAP 0x040
#define MB_FLAG_CONF 0x080
#define MB_FLAG_LOADER 0x100
#define MB_FLAG_APM 0x200
#define MB_FLAG_VBE 0x400

#define MB_BOOTLOADER_MAGIC 0x2BADB002

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

struct multiboot_info{ //#2 (See NOTES.md)
	uintptr_t flags;
	uintptr_t mem_lower;
	uintptr_t mem_upper;
	uintptr_t boot_device;
	uintptr_t cmdline;
	uintptr_t mods_count;
	uintptr_t mods_addr;
	uintptr_t num; // if bit 4 of flag, tabsize
	uintptr_t size; // if bit 4 of flag, strsize
	uintptr_t addr; // if bit 4 of flag, size
	uintptr_t shndx; // if bit 4 of flag, reserved
	uintptr_t mmap_length;
	uintptr_t mmap_addr;
	uintptr_t drives_length;
	uintptr_t drives_addr;
	uintptr_t config_table;
	uintptr_t boot_loader_name;
	uintptr_t apm_table;
	uintptr_t vbe_control_info;
	uintptr_t vbe_mode_info;
	uintptr_t vbe_mode;
	uintptr_t vbe_interface_seg;
	uintptr_t vbe_interface_off;
	uintptr_t vbe_interface_len;
}__attribute__((packed));

struct multiboot_mmap_entry{
	uint32_t size;
	uint64_t addr;
	uint64_t len;
#define MB_MEMORY_AVAILABLE 1
#define MB_MEMORY_RESERVED 2
	uint32_t type;
}__attribute__((packed));

struct multiboot_mod_list{
	uint32_t mod_start;
	uint32_t mod_end;
	uint32_t string;
	uint32_t padding;
}__attribute__((packed));

void check_bootloader_info(uint32_t magic, struct multiboot_info *mb_ptr);
#endif