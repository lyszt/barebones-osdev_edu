#ifndef _TERMINAL_H
#define _TERMINAL_H 1

#include <stddef.h>
#include <stdint.h>
#include <string/string.h>
#include <types/types.h>

class Message {
public:
  const char *content;
  int length;
  int reading_index = 0;
  uint8_t color_byte;

  Message(const char *text) {
    this->content = text;
    this->length = String::length(text);
  }
  pair<bool, char> read() {
    pair<bool, char> reading_content;
    if (content[reading_index] == '\0' || reading_index >= length) {
      reading_content = pair<bool, char>{true, content[reading_index]};
    } else {
      reading_content = pair<bool, char>{false, content[reading_index]};
    }
    reading_index++;
    return reading_content;
  }
};



class Terminal {
public:
  void initialize();
  void newline();
  void putchar(char character);
  void write(Message *text);
  Terminal();

private:
  static const size_t VGA_WIDTH = 80;
  static const size_t VGA_HEIGHT = 25;

  void put_entry_at(unsigned char character, uint8_t color_byte, size_t column,
                    size_t row);

  size_t cursor_row;
  size_t cursor_column;
  uint8_t terminal_color;
  uint16_t *terminal_buffer;
};

extern Terminal terminal;

#endif
