AS       := i686-elf-as
CXX      := i686-elf-g++
CXXFLAGS := -std=gnu++17 -ffreestanding -fno-exceptions -fno-rtti -O2 -Wall -Wextra -Isrc
LDFLAGS  := -ffreestanding -O2 -nostdlib
LIBS     := -lgcc

ASM      := src/asm
LINKER   := $(ASM)/linker.ld

CRTBEGIN := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND   := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)

ASM_OBJS := $(ASM)/boot/boot.o
INIT_HEAD := $(ASM)/crt/init_prologue.o
INIT_TAIL := $(ASM)/crt/init_epilogue.o

OBJS := src/kernel.o src/terminal/terminal.o src/string/string.o

LINK_LIST := $(INIT_HEAD) $(CRTBEGIN) $(ASM_OBJS) $(OBJS) $(CRTEND) $(INIT_TAIL)

.PHONY: all compile clean run run-iso

all: myos

compile: myos.iso

myos: $(INIT_HEAD) $(INIT_TAIL) $(ASM_OBJS) $(OBJS) $(LINKER)
	$(CXX) -T $(LINKER) -o myos $(LDFLAGS) $(LINK_LIST) $(LIBS)

myos.iso: myos grub.cfg
	mkdir -p isodir/boot/grub
	cp myos isodir/boot/myos
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

$(ASM)/crt/init_prologue.o: $(ASM)/crt/init_prologue.s
	$(AS) $< -o $@

$(ASM)/crt/init_epilogue.o: $(ASM)/crt/init_epilogue.s
	$(AS) $< -o $@

$(ASM)/boot/boot.o: $(ASM)/boot/boot.s
	$(AS) $< -o $@

src/kernel.o: src/kernel.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/terminal/terminal.o: src/terminal/terminal.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/string/string.o: src/string/string.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf myos myos.iso isodir $(INIT_HEAD) $(INIT_TAIL) $(ASM_OBJS) $(OBJS)

run: myos
	qemu-system-i386 -kernel myos -display gtk

run-iso: myos.iso
	qemu-system-i386 -cdrom myos.iso -display gtk
