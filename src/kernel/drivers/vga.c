#include "vga.h"

size_t strlen(const char* str){
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;
uint8_t terminal_color = COLOR_ATTR(LGRAY, BLACK);

size_t terminal_row = 0;
size_t terminal_column = 0;
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_put(char c, uint8_t color, size_t x, size_t y){
	const size_t index = y * VGA_COLS + x;
	uint16_t entry = ((uint16_t)c) | ((uint16_t)color)<<8;
	video_memory[index] = entry;
}
 
void terminal_putc(char c){
	if(c == NEWLINE){
		terminal_row++;
		terminal_column = 0;
	}else{
		terminal_put(c, terminal_color, terminal_column, terminal_row);
		if ( ++terminal_column == VGA_COLS ){
			terminal_column = 0;
			if ( ++terminal_row == VGA_ROWS ){
				terminal_row = 0;
			}
		}
	}
}

void update_cursor(void){
	unsigned short position=(terminal_row*VGA_COLS) + terminal_column;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position&0xFF));

	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void terminal_puts(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putc(data[i]);
	update_cursor();
}

void clear_screen(void)
{
	terminal_row = 0;
	terminal_column = 0;
	for (int i = 0; i <= VGA_COLS*VGA_ROWS; i ++)
	{
		terminal_putc(' ');
	}
	terminal_row = 0;
	terminal_column = 0;
	update_cursor();
}