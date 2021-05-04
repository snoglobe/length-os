#include <stdint.h>
#include <stddef.h>

#ifndef PORTS
#define PORTS

void outb(unsigned int port,unsigned char value);
unsigned char inb(unsigned int port);

#endif