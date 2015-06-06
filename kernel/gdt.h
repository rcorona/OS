/*
   gdt.h

   Based off of Bran's Kernel Development tutorial. 

*/

#ifndef _GDT_H
#define _GDT_H

#include "machine.h"

//TODO change if more entries are added to GDT. 
#define GDT_SIZE 3

struct gdt_entry{
	uint16_t limitLow;		//Lower 16 bits of limit
	uint16_t baseLow;		//Lower 16 bits of base. 
	uint8_t baseMiddle;		//Next 8 bits of base
	
	//Access flags, determine what ring segment can be used in.
	uint8_t access;

	//Granularity for blocks (1B or 4KB specified by 0 or 1
	//respectively). 
	uint8_t granularity;
	uint8_t baseHigh; 		//Last 8 bits of base. 
} __attribute__((packed));

struct gdt_ptr{
	uint16_t  limit;		//Size of GDT - 1
	uint32_t base; 			//Base address of first GDT entry.
} __attribute__((packed));	


//Functions to create GDT. 

//Creates a descriptor within the GDT. 
void gdtSetGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, 
		uint8_t gran);

//Sets up GDT pointer, the GDT's first 3 entries (NULL, CS, DS), and calls
//gdt_flush to set up new GDT. 
void gdtInit();

#endif
