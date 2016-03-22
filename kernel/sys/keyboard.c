#include <keyboard.h>
#include <port_io.h>
#include <desc_tables.h>
#include <vga.h>
#include <system.h>

typedef void (*keyboard_handler_t)(uint8_t scancode);

const unsigned char kbd_map[128] = {
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

const unsigned char kbd_map_s[128] = {
  0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
  '(', ')', '_', '+', '\b', /* Backspace */
  '\t',     /* Tab */
  'Q', 'W', 'E', 'R', /* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
  0,      /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
  '"', '~',   0,   /* Left shift */
  '|', 'Z', 'X', 'C', 'V', 'B', 'N',     /* 49 */
  'M', '<', '>', '?',   0,        /* Right shift */
  '*',
  0,  /* Alt */
  ' ',  /* Space bar */
  0,  /* Caps lock */
  0,  /* 59 - F1 key ... > */
  0,   0,   0,   0,   0,   0,   0,   0,
  0,  /* < ... F10 */
  0,  /* 69 - Num lock*/
  0,  /* Scroll Lock */
  0,  /* Home key */
  0,  /* Up Arrow */
  0,  /* Page Up */
  '-',
  0,  /* Left Arrow */
  0,
  0,  /* Right Arrow */
  '+',
  0,  /* 79 - End key*/
  0,  /* Down Arrow */
  0,  /* Page Down */
  0,  /* Insert Key */
  0,  /* Delete Key */
  0,   0,   0,
  0,  /* F11 Key */
  0,  /* F12 Key */
  0,  /* All other keys are undefined */
};

void norm(uint8_t scancode){
  if(scancode & 0x80)
    return;
  if(!kbd_map[scancode])
    return;
  if(keyboard_state.shift){
    putc(kbd_map_s[scancode]);
  }else if(keyboard_state.ctrl){
    putc('^');
    putc(kbd_map_s[scancode]);
  }else{
    putc(kbd_map[scancode]);
  }
}

void shift(uint8_t scancode){
  keyboard_state.shift ^= 1;
}

void ctrl(uint8_t scancode){
  keyboard_state.ctrl ^= 1;
}

void alt(uint8_t scancode){
  keyboard_state.alt ^= 1;
}

void func(uint8_t scancode){

}

keyboard_handler_t key_method[] = {
  NULL, NULL, norm, norm, norm, norm, norm, norm,
  norm, norm, norm, norm, norm, norm, norm, norm,
  norm, norm, norm, norm, norm, norm, norm, norm,
  norm, norm, norm, norm, norm, ctrl, norm, norm,
  norm, norm, norm, norm, norm, norm, norm, norm,
  norm, norm, shift, norm, norm, norm, norm, norm,
  norm, norm, norm, norm, norm, norm, shift, norm,
  alt, norm, NULL, func, func, func, func, func,
  func, func, func, func, func, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, func,
  func, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

void kbd_handler(struct registers regs){
	uint8_t scancode;
	scancode = inb(0x60);

	keyboard_handler_t handler;
  handler = key_method[scancode & 0x7f];
  if(handler){
    handler(scancode);
  }
}

void kbd_install(){
	irq_install_handler(1, &kbd_handler);
}