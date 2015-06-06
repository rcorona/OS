/*
   Rodolfo Corona Rodriguez
   gdt.cc

   Based off of Bran's Kernel Development Tutorial. 
*/

#include "gdt.h"

//Will contain 3 entries. NULL descriptor, CS, and DS. 
struct gdt_entry gdt[3];
struct gdt_ptr gdtPtr;

void gdtSetGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access,
		uint8_t gran){
	
	//Set up the descriptor's base address.
	gdt[num].baseLow = base & 0xFFFF;
	gdt[num].baseMiddle = (base >> 16) & 0xFF;
	gdt[num].baseHigh = (base >> 24) & 0xFF;

	//Set up the descriptor's limits and granularity. 
	gdt[num].limitLow = limit & 0xFFFF;
	gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0); 

	//Set up descriptor's access. 
	gdt[num].access = access; 
}

void gdtInit(){
	//GDT will have 3 entries.
	gdtPtr.limit = (sizeof(struct gdt_entry) * GDT_SIZE) - 1;
	
	//Base is address of GDT. 
	gdtPtr.base = (uint32_t)&gdt;

	//NULL descriptor. 
	gdtSetGate(0, 0, 0, 0, 0); 

	//CS entry. Base address = 0, limit = 4GB,
	//has 4KB granularity, uses 32-bit opcodes,
	//and is a CS descriptor. 
	gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	//DS entry. Same as CS entry except its
	//descriptor type specifies DS segment. 
	gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 

	//Flush old GDT to install new one. 
	gdt_flush(); 
}
