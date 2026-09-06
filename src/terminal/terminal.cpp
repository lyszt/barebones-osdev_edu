#include <stddef.h>
#include <stdint.h>

#include <string/string.h>
#include <terminal/terminal.h>
#include <vga/vga.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = reinterpret_cast<uint16_t *>(0xB8000);

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;
  for (size_t row = 0; row < VGA_HEIGHT; row++) {
    for (size_t column = 0; column < VGA_WIDTH; column++) {
      const size_t buffer_index = row * VGA_WIDTH + column;
      terminal_buffer[buffer_index] = vga_entry(' ', terminal_color);
    }
  }
}

static void terminal_put_entry_at(unsigned char character, uint8_t color_byte,
                                  size_t column, size_t row) {
  const size_t buffer_index = row * VGA_WIDTH + column;
  terminal_buffer[buffer_index] = vga_entry(character, color_byte);
}

void terminal_putchar(char character) {

  // Character handling
  unsigned char unsigned_character = character;
  switch (unsigned_character) {
  case '\n':
    ++terminal_row;
    terminal_column = 0;
    return;
  default:
    break;
  }

  terminal_put_entry_at(unsigned_character, terminal_color, terminal_column,
                        terminal_row);
  if (++terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT)
      terminal_row = 0;
  }
}

void terminal_write(const char *text_data, size_t text_length) {
  for (size_t index = 0; index < text_length; index++)
    terminal_putchar(text_data[index]);
}

void terminal_writestring(const char *text) {
  terminal_write(text, strlen(text));
}
