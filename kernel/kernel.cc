/****************************************
  kernel.cc

  Code for a very basic kernel
******************************************/

#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include "gdt.h"
#include "idt.h"
#include "pit.h"
#include "keyboard.h"
#include "heap.h" 

/*Checks for cross compiler targeting issues */
#if defined(__linux__)
#error "Cross compiler targeting Linux"
#endif

/*Checks for 32-bit ix86 target*/
#if !defined(__i386__)
#error "Not using an ix86-elf compiler"
#endif

//Definition of __cxa_pure_virtual, necessary for pure virtual
//functions. 
extern "C" void __cxa_pure_virtual() { while (1); }

//Magic break point for BOCHS. 
#define MAGIC_BREAK asm volatile ("xchg %bx, %bx");

#if defined(__cplusplus)
extern "C" //use C linkage for kernel main
#endif
void kernel_main(){
	//Creates and installs GDT. 
	gdtInit(); 

	//Creates and installs IDT. 
	idtInit();

	//Initializes VGA
	VGA::init(); 

	//Initializes PIT. 
	initPIT(PIT_FREQ);

	//Initializes heap. 
	Heap::init(HEAP_START, HEAP_SIZE); 
}
