#include <stddef.h>
#include <stdint.h>

#ifndef HEAP_H
#define HEAP_H

typedef struct _KHEAPBLOCKSS {
	struct _KHEAPBLOCKSS	*next;
	uint32_t					top;
	uint32_t					max;
	uintptr_t					size;			/* total size in bytes including this header */
} KHEAPBLOCKSS;

typedef struct _KHEAPSS {
	KHEAPBLOCKSS			*fblock;
	uint32_t					bsize;
} KHEAPSS;

void k_heapSSInit(KHEAPSS *heap, uint32_t bsize);
int k_heapSSAddBlock(KHEAPSS *heap, uintptr_t addr, uint32_t size);
void *k_heapSSAlloc(KHEAPSS *heap, uint32_t size);
void k_heapSSFree(KHEAPSS *heap, void *ptr);

#endif