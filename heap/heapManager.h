#include <stddef.h>
#include <stdint.h>

#ifndef HEAPMANAGER_H
#define HEAPMANAGER_H

void initHeap();
void* kmalloc(uint32_t size);
void kfree(void *toFree);

#endif