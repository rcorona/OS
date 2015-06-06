/*
   Rodolfo Corona Rodriguez
   idt.h

   Based off of idt. c in Bran's Kernel Development Tutorial. 
   it can be found at www.osdever.net/bkerndev/Docs/idt.htm
*/

#ifndef _IDT_H
#define _IDT_H

#include "machine.h"
#include "stdio.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define IRQ0 32
#define IRQ1 33

typedef void (*handlerP)(struct regs *); 

/*
NOTE:
  There are four Initialization Control Words that are given
  to both the master and slave PICs during initialization. 

ICW1: initialization information, i.e. what PIC should expect.
	  Includes whether cascading is to be expected, etc. 

ICW2: Maps base address of IRQs within IDT for each PIC. 

ICW3: Used to specify which IRQ lines the master and slave
	  PICs should use to communicate with each other. 

	  For master: Bit set in byte (i.e. one of eight) specifies
	  which line to use. i.e. 0x04 = 0100 which means the third
	  IRQ line is to be used which corresponds to IRQ2. 

	  For slave: IRQ number that the master uses to communicate
	  with slave in binary notation. So 0x2 will specify IRQ2
	  as being the one used by the master to communicate with 
	  the slave.

ICW4: Controls how PIC is to operate. If first bit is set,
	  then the PIC is in 80x86 mode. 
*/

#define ICW1_INIT 0x10 	//Tells PIC to expect initialization. 
#define ICW1_ICW4 0x01	//Tells PIC to expect ICW4

#define ICW4_8086 0x1	//Specifies 80x86 mode. 

struct idt_entry{
	uint16_t baseLow;		//Low 16 bits of base address. 
	uint16_t segSelector;	//The code segment selector (e.g. CS). 
	uint8_t zero;			//Always 0 by convention. 
	

	/*Type attributes for the gate. 
	  Contains gate type, whether its a storage segment or not,
	  DPL, and the P bit.*/ 
	uint8_t typeAttr;			
	
	uint16_t baseHigh;		//High 16 bits for the base address. 
} __attribute__((packed));

struct idt_ptr{
	uint16_t limit;			//Size of IDT - 1
	uint32_t base; 			//Base address of IDT. 
} __attribute__((packed));

//Represents items pushed to stack before calling fault_handler.
struct regs{
	uint32_t gs, fs, es, ds;

	//pusha
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 

	uint32_t isrNum, errCode; 

	//These are pushed by the processor when interrupt occurs. 
	uint32_t eip, cs, eflags, usrEsp, ss;
};

//Creates a gate (i.e. an entry) in the IDT. 
void idtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

//Installs the IDT. 
void idtInit();

//Remaps the IRQs to IDT entries 32-47.
void remapIRQs();

//Installs an IRQ handler. 
void installISRHandler(uint32_t isr, handlerP handler);

//Uninstalls the IRQ handler for a given entry. 
void uninstallISRHandler(uint32_t isr);

//Handlers for exceptions and IRQs. 
extern "C" void fault_handler(struct regs *r);
extern "C" void irq_handler(struct regs *r); 

#endif

