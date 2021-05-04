#include <stdint.h>
#include <stddef.h>

#ifndef VIDEO
#define VIDEO

void term_init();
void term_putc(char c);
void term_print(const char* str);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();
void update_cursor(int x, int y);
void scroll();
void backspace();
void term_putc_x_y(char c, int x, int y);

#endif