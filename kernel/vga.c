#include <vga.h>

uint16_t* video_memory;
uint8_t terminal_color = COLOR_ATTR(LGRAY, BLACK);

size_t terminal_row = 0;
size_t terminal_column = 0;
 
void init_video(){
	video_memory = (uint16_t*) VIDEO_MEMORY;
	clear();
}

void update_cursor(){
	uint16_t pos = (terminal_row*VGA_COLS) + terminal_column;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));

	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void clear(){
	uint16_t blank = 0x20 | (terminal_color << 8);

	memsetw(video_memory, blank, VGA_COLS*VGA_ROWS);

	terminal_row = 0;
	terminal_column = 0;
	update_cursor();
}

void scroll(){
	uint16_t blank = 0x20 | (terminal_color << 8);

	size_t shift = 0;
	if(terminal_row >= VGA_ROWS){
		shift = terminal_row - VGA_ROWS + 1;
		memcpy((uint8_t*)video_memory, (uint8_t*)(video_memory + (shift * VGA_COLS)), (VGA_ROWS - shift) * VGA_COLS * 2);

		memsetw(video_memory + (VGA_ROWS - shift) * VGA_COLS, blank,  VGA_COLS);
		terminal_row = VGA_ROWS - 1;
	}
}

void put(char c, size_t x, size_t y){
	size_t index = y * VGA_COLS + x;
	uint16_t entry = ((uint16_t)c) | ((uint16_t)terminal_color)<<8;
	video_memory[index] = entry;
}

void setcolor(uint8_t color){
	terminal_color = color;
}
 
void putc(char c){
	if(c == BACKSPACE){
		if(terminal_column != 0)
			terminal_column--;
	}else if(c == TAB){
		terminal_column = (terminal_column + 8) & ~(8 - 1);
	}else if(c == NEWLINE){
		terminal_row++;
		terminal_column = 0;
	}else if(c == CR){
		terminal_column = 0;
	}else if(c >= ' '){
		put(c, terminal_column, terminal_row);
		terminal_column++;
	}

	if(terminal_column >= VGA_COLS){
		terminal_column = 0;
		terminal_row++;
	}

	scroll();
	update_cursor();
}



void puts(char* str){
	size_t len = strlen(str);
	for ( size_t i = 0; i < len; i++ )
		putc(str[i]);
}

