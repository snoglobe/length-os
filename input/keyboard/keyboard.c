#include "keyboard.h"
#include "../../video/video.h"
#include "../../ports/ports.h"
#include "../../heap/heap.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

char lastChar;

int kbd_irq;

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};	

void init_keyboard()
{
    outb(0x20 , 0x11);
	  outb(0xA0 , 0x11);

	  outb(0x21 , 0x20);
	  outb(0xA1 , 0x28);

	  outb(0x21 , 0x00);  
	  outb(0xA1 , 0x00);  

	  outb(0x21 , 0x01);
	  outb(0xA1 , 0x01);

	  outb(0x21 , 0xff);
	  outb(0xA1 , 0xff);
    outb(0x21 , 0xFD);

    asm volatile ("sti");
}

void keyboard_handler_c()
{
    unsigned char scancode;
    unsigned char status;
    
    outb(0x20, 0x20);

    status = inb(KEYBOARD_STATUS_PORT);

    if(status & 0x01)
    {
        scancode = inb(KEYBOARD_DATA_PORT);
        if (scancode < 0)
            return;

        if (!(scancode & 0x80))
        {
            lastChar = kbdus[scancode];
            kbd_irq = 1;
            term_putc(lastChar);
        }
    }
}

char get_char()
{
   while(kbd_irq != 1);
   kbd_irq = 0;
   return lastChar;
}

char* get_string()
{
    char* strbuffer = (char*)kmalloc(sizeof(char) * 255);
    int index = 0;
    while(get_char() != '\0' || get_char() != '\n')
    {
      strbuffer[index] = get_char();
      index++;
    }
    return strbuffer;
}