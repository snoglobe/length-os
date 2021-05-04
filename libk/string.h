#include <stddef.h>
#include <stdint.h>

#ifndef STRING_H
#define STRING_H

int memcmp(const void*, const void*, size_t);
void* memcpy(void* dest, const void* src, int count);
void* memmove(void*, const void*, size_t);
void* memset(void* dest, unsigned char val, int count);
unsigned short* memsetw(unsigned short* dest, unsigned short val, int count);
size_t strlen(const char*);

#endif