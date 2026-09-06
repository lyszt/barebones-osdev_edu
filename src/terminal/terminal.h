#ifndef _TERMINAL_H
#define _TERMINAL_H 1

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char character);
void terminal_write(const char* text_data, size_t text_length);
void terminal_writestring(const char* text);

#endif
