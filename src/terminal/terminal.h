#ifndef _TERMINAL_H
#define _TERMINAL_H 1

#include <stddef.h>
#include <stdint.h>
#include <string/string.h>
#include <types/types.h>

class Message;

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

enum charType { REGULAR, END_STRING, LINE_BREAK };

class Message {
public:
  const char *content;
  int length;
  int reading_index = 0;
  uint8_t color_byte;
  Terminal *terminal;

  Message(const char *text, Terminal *terminal) {
    this->content = text;
    this->terminal = terminal;
    this->length = String::length(text);
  }

  pair<bool, char> read() {
    char c = content[reading_index];

    switch (readSpecialChars(c)) {
    case LINE_BREAK:
      terminal->newline();
      reading_index++;
      return pair<bool, char>{false, c};
    case END_STRING:
      reading_index++;
      return pair<bool, char>{true, c};
    case REGULAR:
      break;
    }

    if (reading_index >= length)
      return pair<bool, char>{true, c};

    terminal->putchar(c);
    reading_index++;
    return pair<bool, char>{false, c};
  }

private:
  charType readSpecialChars(char unsigned_char) {
    switch (unsigned_char) {
    case '\n':
      return LINE_BREAK;
    case '\0':
      this->reading_index = this->length;
      return END_STRING;
    default:
      return REGULAR;
    }
  }
};

#endif
