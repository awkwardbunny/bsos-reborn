#ifndef VGA_H
#define VGA_H

#include "system.h"
#include "vga_constants.h"
#include "port_io.h"

void init_video();
void clear();
void put(char c, size_t x, size_t y);
void putc(char c);
void puts(char *str);
void setcolor(uint8_t color);

#endif