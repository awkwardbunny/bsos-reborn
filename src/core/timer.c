#include "timer.h"
#include "desc_tables.h"
#include "port_io.h"
#include "vga.h"

int timer_ticks = 0;
int timer_hz = 18;
int seconds = 0;

void timer_phase(int hz){
	timer_hz = hz;
	int divisor = 1193180 / hz;
	outb(0x43, 0x36);
	outb(0x40, divisor & 0xFF);
	outb(0x40, divisor >> 8);
}

void timer_handler(struct registers regs){
	timer_ticks++;

	if(timer_ticks % timer_hz == 0){
		seconds++;
		if(seconds > 9)
			seconds = 0;

		put('0'+seconds, VGA_COLS-1, 0); //display last digit on top-right
	}
}

void timer_install(){
	irq_install_handler(0, &timer_handler);
}

void timer_wait(int ticks){
	unsigned long eticks;

	eticks = timer_ticks + ticks;
	while(timer_ticks < eticks);
}