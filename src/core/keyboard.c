#include <keyboard.h>
#include <port_io.h>
#include <desc_tables.h>
#include <vga.h>

unsigned char kbd_map[128] = {
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
  0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
  '\'', '`',   0,		/* Left shift */
  '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
  0,	/* Alt */
  ' ',	/* Space bar */
  0,	/* Caps lock */
  0,	/* 59 - F1 key ... > */
  0,   0,   0,   0,   0,   0,   0,   0,
  0,	/* < ... F10 */
  0,	/* 69 - Num lock*/
  0,	/* Scroll Lock */
  0,	/* Home key */
  0,	/* Up Arrow */
  0,	/* Page Up */
  '-',
  0,	/* Left Arrow */
  0,
  0,	/* Right Arrow */
  '+',
  0,	/* 79 - End key*/
  0,	/* Down Arrow */
  0,	/* Page Down */
  0,	/* Insert Key */
  0,	/* Delete Key */
  0,   0,   0,
  0,	/* F11 Key */
  0,	/* F12 Key */
  0,	/* All other keys are undefined */
};

void kbd_handler(struct registers regs){
	uint8_t scancode;
	scancode = inb(0x60);

	if(scancode & 0x80){
		/* A KEY WAS RELEASED */
	}else{
    if(scancode == 0x44) /* F10 */
      clear();
    if(scancode == 0x3d) /* F3 */
      setcolor(0x12);
    if(scancode == 0x3e) /* F4 */
      setcolor(0x34);
    if(scancode == 0x3f) /* F5 */
      setcolor(0x56);
    if(scancode == 0x40) /* F6 */
      setcolor(0x78);
    if(scancode == 0x41) /* F7 */
      setcolor(0x0A); /* Matrix Colors */
    if(scancode == 0x42) /* F8 */
      setcolor(0x8A); /* Matrix Blink */
    if(scancode == 0x43) /* F9 */
      setcolor(0x07);    /* Reset Colors */
		putc(kbd_map[scancode]);
	}
}

void kbd_install(){
	irq_install_handler(1, &kbd_handler);
}