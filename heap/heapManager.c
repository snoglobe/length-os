#include "heapManager.h"
#include "heap.h"

KHEAPSS *heap;

void initHeap()
{
    k_heapSSInit(heap, 64);
}

void* kmalloc(uint32_t size)
{
    return k_heapSSAlloc(heap, size);
}

void kfree(void *toFree)
{
    k_heapSSFree(heap, toFree);
}