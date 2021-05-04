#include "isr.h"
#include "../video/video.h"
#include "../input/keyboard/keyboard.h"

void isr_handler(registers_t regs)
{
    term_print("Interrupt test\n");
}
