#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stddef.h>
#include "vga_constants.h"
#include "port_io.h"

size_t strlen(const char* str);
void terminal_setcolor(uint8_t color);
void terminal_put(char c, uint8_t color, size_t x, size_t y);
void terminal_putc(char c);
void update_cursor();
void terminal_puts(const char* data);
void clear_screen(void);

#endif