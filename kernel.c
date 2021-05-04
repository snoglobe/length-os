#include <stddef.h>
#include <stdint.h>

#include "video/video.h"
#include "desc_tables/descriptor_tables.h"
#include "input/keyboard/keyboard.h"
#include "heap/heapManager.h"

void kernel_main()
{
    init_descriptor_tables();
    init_keyboard();
    term_init();

    initHeap();

    term_print("Length OS starting. . . \n");
    term_print("Welcome to Length OS!\n");

    asm volatile ("int $0x1");

    while(1)
    {
        term_print("prompt >>");
        char* typed = get_string();
        term_print(typed);
    }

    term_print("exit main");
}