#include "vga.h"

uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;
unsigned short cursor_pos = 0;
uint8_t terminal_color;

void printch(char ch){
	video_memory[cursor_pos] = ch | terminal_color << 8;
	cursor_pos++;
}

void prints(char* str)
{
	while (*str)
	{
		printch(*str);
		str++;
	}
}

void init_terminal(uint8_t tc){
	terminal_color = tc;
}

/*	clear_screen
	clear the screen entirely, setting the cursor to the top left corner
*/
void clear_screen(void)
{
	for (int i = 0; i <= 8000; i += 2)
	{
		video_memory[i] = ' ';
	}
}
