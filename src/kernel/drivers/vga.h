#ifndef VGA_H
#define VGA_H

#include "vga_constants.h"

void printch(char);
void prints(char*);
void init_terminal(uint8_t);
void clear_screen(void);

#endif /* VGA_H */
