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

	putchar('H'); 

	puts("elloo, kernel World!\n"); 
	puts("How are you?\n");

	printf("HELLO AGAIN\n");

	int testNum = 0xFFFFFFFF;

	printf("Num before: %x\n", testNum); 

	memset(&testNum, 0xAA, sizeof(int));

	printf("Num after: %x\n", testNum);

	//putchar((char)(1/0)); //Not working: 0, 8, 10,  
}
