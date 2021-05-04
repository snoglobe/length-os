#ifndef PAGING_H
#define PAGING_H

#include <stddef.h>
#include <stdint.h>
#include "../video/video.h"

void init_paging();
void* requestPage();

#endif