AS       := i686-elf-as
CXX      := i686-elf-g++
CXXFLAGS := -std=gnu++17 -ffreestanding -fno-exceptions -fno-rtti -O2 -Wall -Wextra -Isrc
LDFLAGS  := -ffreestanding -O2 -nostdlib
LIBS     := -lgcc

OBJS := src/boot.o src/kernel/kernel.o src/terminal/terminal.o src/string/strlen.o

.PHONY: all compile clean run run-iso

all: myos

compile: myos.iso

myos: $(OBJS) src/linker.ld
	$(CXX) -T src/linker.ld -o myos $(LDFLAGS) $(OBJS) $(LIBS)

myos.iso: myos grub.cfg
	mkdir -p isodir/boot/grub
	cp myos isodir/boot/myos
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

src/boot.o: src/boot.s
	$(AS) src/boot.s -o src/boot.o

src/kernel/kernel.o: src/kernel/kernel.cpp
	$(CXX) $(CXXFLAGS) -c src/kernel/kernel.cpp -o src/kernel/kernel.o

src/terminal/terminal.o: src/terminal/terminal.cpp
	$(CXX) $(CXXFLAGS) -c src/terminal/terminal.cpp -o src/terminal/terminal.o

src/string/strlen.o: src/string/strlen.cpp
	$(CXX) $(CXXFLAGS) -c src/string/strlen.cpp -o src/string/strlen.o

clean:
	rm -rf myos myos.iso isodir $(OBJS)

run: myos
	qemu-system-i386 -kernel myos -display gtk

run-iso: myos.iso
	qemu-system-i386 -cdrom myos.iso -display gtk
