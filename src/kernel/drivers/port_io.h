#ifndef PORT_IO_H
#define PORT_IO_H

unsigned char inb(unsigned short);
unsigned short inw(unsigned short);
void outb(unsigned short, unsigned char);
void outw(unsigned short, unsigned short);

#endif