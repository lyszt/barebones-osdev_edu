#ifndef _MESSAGE_H
#define _MESSAGE_H 1

#include <stdint.h>

#include <terminal/terminal.h>
#include <types/types.h>

enum charType { REGULAR, END_STRING, LINE_BREAK };

class Message {
public:
  const char *content;
  int length;
  int reading_index = 0;
  uint8_t color_byte;
  Terminal *terminal;

  Message(const char *text, Terminal *terminal);

  pair<bool, char> read();

private:
  charType readSpecialChars(char character);
};

#endif
