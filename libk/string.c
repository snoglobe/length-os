#include "string.h"
 
int memcmp(const void* aptr, const void* bptr, size_t size) {
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}


void* memset(void* dest, unsigned char val, int count)
{
	unsigned char* destC = (unsigned char*)dest;
	int i;
	for (i = 0; i < count; i++)
		destC[i] = val;
	return dest;
}

unsigned short* memsetw(unsigned short* dest, unsigned short val, int count)
{
	int i;
	for (i = 0; i < count; i++)
		dest[i] = val;
	return dest;
}


void* memcpy(void* dest, const void* src, int count)
{
	unsigned char* destC = (unsigned char*)dest;
	unsigned char* srcC = (unsigned char*)src;
	int i;
	for (i = 0; i < count; i++)
		destC[i] = srcC[i];
	return dest;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}