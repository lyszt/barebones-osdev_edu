#include <stddef.h>
#include <stdint.h>

#include <string/string.h>
#include <terminal/terminal.h>
#include <vga/vga.h>

static uint16_t *const VGA_MEMORY = reinterpret_cast<uint16_t *>(0xB8000);

Terminal terminal;

void Terminal::initialize() {
  this->cursor_row = 0;
  this->cursor_column = 0;
  this->terminal_color = Vga::entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  this->terminal_buffer = VGA_MEMORY;
  for (size_t row = 0; row < VGA_HEIGHT; row++) {
    for (size_t column = 0; column < VGA_WIDTH; column++) {
      const size_t buffer_index = row * VGA_WIDTH + column;
      this->terminal_buffer[buffer_index] = Vga::entry(' ', this->terminal_color);
    }
  }
}

void Terminal::put_entry_at(unsigned char character, uint8_t color_byte,
                            size_t column, size_t row) {
  const size_t buffer_index = row * VGA_WIDTH + column;
  this->terminal_buffer[buffer_index] = Vga::entry(character, color_byte);
}

void Terminal::newline() {
  ++this->cursor_row;
  this->cursor_column = 0;
}

void Terminal::putchar(char character) {

  // Character handling
  unsigned char unsigned_character = character;
  switch (unsigned_character) {
  case '\n':
    this->newline();
    return;
  default:
    break;
  }

  this->put_entry_at(unsigned_character, this->terminal_color, this->cursor_column,
                     this->cursor_row);
  if (++this->cursor_column == VGA_WIDTH) {
    this->cursor_column = 0;
    if (++this->cursor_row == VGA_HEIGHT)
      this->cursor_row = 0;
  }
}

void Terminal::write(const char *text_data, size_t text_length) {
  for (size_t index = 0; index < text_length; index++)
    this->putchar(text_data[index]);
}

void Terminal::writestring(const char *text) {
  this->write(text, String::length(text));
}
