#include <kernel.h>
#include <message/message.h>
#include <stddef.h>
#include <stdint.h>
#include <terminal/terminal.h>

#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

extern "C" void kernel_main(void) {
  Kernel kernel;
  kernel.write("Hello Kernel World!\n");
}

Kernel::Kernel() {}

void Kernel::write(const char *text) {
  Message message(text, &this->terminal);
  this->terminal.write(&message);
}