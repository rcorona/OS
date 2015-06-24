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
#include "heap.h"
#include "tests.h"
#include "vmm.h"
#include "pit.h"
#include "keyboard.h"

/*Checks for cross compiler targeting issues */
#if defined(__linux__)
#error "Cross compiler targeting Linux"
#endif

/*Checks for 32-bit ix86 target*/
#if !defined(__i386__)
#error "Not using an ix86-elf compiler"
#endif

//For Virtual functions. TODO move somewhere more standard. 
extern "C" void __cxa_pure_virtual() { while(true); }

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

	//Initializes PIT
	initPIT(PIT_FREQ); 

	//Initializes heap. 
	Heap::init((void *)HEAP_START, HEAP_SIZE);

	//Initializes physical memory frames. 
	PhysMem::init((uint32_t)HEAP_END, 0xFFFFFFFF);
}
