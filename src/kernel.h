#ifndef KERNEL_H
#define KERNEL_H

#include <terminal/terminal.h>

class Kernel {
public:
  Terminal terminal;
  Kernel();
  void write(const char *text);
};

#endif