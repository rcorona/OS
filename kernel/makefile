TARGET= i686-elf
ASM= nasm -f elf
CC= $(TARGET)-g++
CFLAGS= -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -std=c++11
OS= os.bin
SOURCES= boot.o kernel.o vga.o stdio.o gdt.o idt.o machine.o pit.o keyboard.o heap.o

all: kernel

kernel: $(SOURCES)
	$(CC) -T linker.ld -o kernel -ffreestanding -O2 -nostdlib $(SOURCES) -lgcc

boot.o: boot.s
	$(ASM) boot.s

machine.o: machine.s
	$(ASM) machine.s

kernel.o: kernel.cc vga.cc stdio.cc stdio.h
	$(CC) -c kernel.cc -o kernel.o $(CFLAGS) 

vga.o:
	$(CC) -c vga.cc -o vga.o $(CFLAGS)

stdio.o:
	$(CC) -c stdio.cc -o stdio.o $(CFLAGS)

gdt.o:
	$(CC) -c gdt.cc -o gdt.o $(CFLAGS)

idt.o:
	$(CC) -c idt.cc -o idt.o $(CFLAGS)

pit.o:
	$(CC) -c pit.cc -o pit.o $(CFLAGS)

keyboard.o:
	$(CC) -c keyboard.cc -o keyboard.o $(CFLAGS)

heap.o:
	$(CC) -c heap.cc -o heap.o $(CFLAGS)

clean:
	rm -rf *o

dump:
	objdump -D kernel > odump.txt
	vim odump.txt
