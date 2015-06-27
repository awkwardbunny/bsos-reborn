#ifndef PAGING_H
#define PAGING_H

/* From http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html */
#include <system.h>
#include <desc_tables.h>

typedef struct page {
   uint32_t present    : 1;   // Page present in memory
   uint32_t rw         : 1;   // Read-only if clear, readwrite if set
   uint32_t user       : 1;   // Supervisor level only if clear
   uint32_t accessed   : 1;   // Has the page been accessed since last refresh?
   uint32_t dirty      : 1;   // Has the page been written to since last refresh?
   uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
   uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
}__attribute__((packed)) page_t;

typedef struct page_table {
   page_t pages[1024];
}__attribute__((packed)) page_table_t;

typedef struct page_directory {
   page_table_t *tables[1024];
   uint32_t tablesPhysical[1024];
   uint32_t physicalAddr;
}__attribute__((packed)) page_directory_t;

page_directory_t * kernel_directory;
page_directory_t * current_directory;

void init_paging();
void switch_page_directory(page_directory_t *new);
page_t *get_page(uint32_t address, int make, page_directory_t *dir);

void page_fault(struct registers regs);

#endif