#ifndef _TERMINAL_H
#define _TERMINAL_H 1

#include <stddef.h>
#include <stdint.h>

class Terminal {
public:
	void initialize();
	void newline();
	void putchar(char character);
	void write(const char* text_data, size_t text_length);
	void writestring(const char* text);

private:
	static const size_t VGA_WIDTH = 80;
	static const size_t VGA_HEIGHT = 25;

	void put_entry_at(unsigned char character, uint8_t color_byte, size_t column, size_t row);

	size_t cursor_row;
	size_t cursor_column;
	uint8_t terminal_color;
	uint16_t* terminal_buffer;
};

extern Terminal terminal;

#endif
