#include <stdint.h>
#include <stddef.h>

#include "../../desc_tables/isr.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H	
void keyboard_handler_c();
void init_keyboard();
char* get_string();
char get_char();
#endif