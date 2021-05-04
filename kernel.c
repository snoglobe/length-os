#include <stddef.h>
#include <stdint.h>

#include "video/video.h"
#include "desc_tables/descriptor_tables.h"
#include "input/keyboard/keyboard.h"
#include "heap/heapManager.h"
#include "paging/paging.h"

void kernel_main()
{
    init_descriptor_tables();
    init_keyboard();
    term_init();

    initHeap();

    term_print("Length OS starting. . . \n");
    term_print("Welcome to Length OS!\n");

    init_paging();

    asm volatile ("int $0x1");

    while(1)
    {
        
    }

    term_print("exit main");
}