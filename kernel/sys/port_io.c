#include <port_io.h>

unsigned char inb(unsigned short port)
{
	unsigned char value;
	__asm__(
		"in %%dx, %%al" :
		"=a" (value) :
		"d" (port)
		);
	return value;
}

unsigned short inw(unsigned short port)
{
	unsigned short value;
	__asm__(
		"in %%dx, %%ax" :
		"=a" (value) :
		"d" (port)
		);
	return value;
}

void outb(unsigned short port, unsigned char data)
{
	__asm__(
		"out %%al, %%dx" : :
		"a" (data),
		"d" (port)
		);
}

void outw(unsigned short port, unsigned short data)
{
	__asm__(
		"out %%ax, %%dx" : :
		"a" (data),
		"d" (port)
		);
}