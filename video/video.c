#include "video.h"
#include "../ports/ports.h"
#include "../libk/string.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
uint8_t* vga_buffer_u8 = (uint8_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;

uint16_t get_char_value(char c)
{
	return ((uint16_t)term_color << 8) | c;
}

void scroll()
{
    unsigned blank, temp;
	blank = get_char_value(' ');
	temp = term_row - VGA_ROWS + 1;
	memcpy(vga_buffer, vga_buffer + temp * VGA_COLS, (VGA_ROWS - temp) * VGA_COLS * 2);
	memsetw(vga_buffer + (VGA_ROWS - temp) * VGA_COLS, blank, VGA_COLS);
	term_row = VGA_ROWS - 1;
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_COLS + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void term_init()
{
	for (int col = 0; col < VGA_COLS; col ++)
	{
		for (int row = 0; row < VGA_ROWS; row ++)
		{
			const size_t index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
		}
	}
    enable_cursor(0, 15);
}

void term_putc(char c)
{
	switch (c)
	{
	case '\n': 
		{
			term_col = 0;
			term_row ++;
			break;
		}
 
	default: 
		{
			const size_t index = (VGA_COLS * term_row) + term_col; 
			vga_buffer[index] = ((uint16_t)term_color << 8) | c;
			term_col ++;
			break;
		}
	}
 
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		term_row ++;
	}

	if (term_row >= VGA_ROWS)
	{
		term_col = 0;
		scroll();
	}

    update_cursor(term_col, term_row);
}

void term_putc_x_y(char c, int x, int y)
{
	const size_t index = (VGA_COLS * y) + x; 
	vga_buffer[index] = ((uint16_t)term_color << 8) | c;
	term_col ++;
}

void term_print(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; i ++)
    	term_putc(str[i]);
}
 