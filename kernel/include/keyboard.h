#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <system.h>

struct keyboard_states{
	uint32_t shift : 1;
	uint32_t ctrl : 1;
	uint32_t alt : 1;
} keyboard_state;

void kbd_install();

#endif