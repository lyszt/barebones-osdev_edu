#include <message/message.h>
#include <string/string.h>

Message::Message(const char *text, Terminal *terminal) {
  this->content = text;
  this->terminal = terminal;
  this->length = String::length(text);
}

pair<bool, char> Message::read() {
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

charType Message::readSpecialChars(char character) {
  switch (character) {
  case '\n':
    return LINE_BREAK;
  case '\0':
    this->reading_index = this->length;
    return END_STRING;
  default:
    return REGULAR;
  }
}
