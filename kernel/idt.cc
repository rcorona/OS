/*
   Rodolfo Corona Rodriguez
   idt.cc

   Based off of idt.c from Bran's Kernel Development Tutorial
   which can be found at www.osdever.net/bkerndev/Docs/idt.htm
*/

#include "idt.h"

/*NOTE: If an undefined IDT entry is hit, it will usually 
cause an unhandled interrupt exception. This will occur
if the present bit (i.e. P bit) is cleared in the entry.*/
struct idt_entry idt[256];	//There are 256 IDT entries by convention. 
struct idt_ptr idtPtr;		//Ptr to be used to load IDTR. 
handlerP isrHandlers[256]; 	//Contains isr handlers.  

void idtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t typeAttr){
	//Sets base in descriptor. 
	idt[num].baseLow = base & 0xFFFF;
	idt[num].baseHigh = (base >> 16) & 0xFFFF;

	//Sets selector.
	idt[num].segSelector = selector;

	//Sets 0's by convention. 
	idt[num].zero = 0;

	//Sets gate attributes. 
	idt[num].typeAttr = typeAttr;
}

void idtInit(){
	//Sets idt pointer up for lidt instruction. 
	idtPtr.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtPtr.base = (uint32_t)&idt;

	//Clears out IDT, initializing it to all 0's. 
	memset(&idt, 0, sizeof(struct idt_entry) * 256);

	//Adds exceptions to IDT. 
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(1, (uint32_t)isr1, 0x08, 0x8E);
	idtSetGate(2, (uint32_t)isr2, 0x08, 0x8E);
	idtSetGate(3, (uint32_t)isr3, 0x08, 0x8E);
	idtSetGate(4, (uint32_t)isr4, 0x08, 0x8E);
	idtSetGate(5, (uint32_t)isr5, 0x08, 0x8E);
	idtSetGate(6, (uint32_t)isr6, 0x08, 0x8E);
	idtSetGate(7, (uint32_t)isr7, 0x08, 0x8E);
	idtSetGate(8, (uint32_t)isr8, 0x08, 0x8E);
	idtSetGate(9, (uint32_t)isr9, 0x08, 0x8E);
	idtSetGate(10, (uint32_t)isr10, 0x08, 0x8E);
	idtSetGate(11, (uint32_t)isr11, 0x08, 0x8E);
	idtSetGate(12, (uint32_t)isr12, 0x08, 0x8E);
	idtSetGate(13, (uint32_t)isr13, 0x08, 0x8E);
	idtSetGate(14, (uint32_t)isr14, 0x08, 0x8E);
	idtSetGate(15, (uint32_t)isr15, 0x08, 0x8E);
	idtSetGate(16, (uint32_t)isr16, 0x08, 0x8E);
	idtSetGate(17, (uint32_t)isr17, 0x08, 0x8E);
	idtSetGate(18, (uint32_t)isr18, 0x08, 0x8E);
	idtSetGate(19, (uint32_t)isr19, 0x08, 0x8E);
	idtSetGate(20, (uint32_t)isr20, 0x08, 0x8E);
	idtSetGate(21, (uint32_t)isr21, 0x08, 0x8E);
	idtSetGate(22, (uint32_t)isr22, 0x08, 0x8E);
	idtSetGate(23, (uint32_t)isr23, 0x08, 0x8E);
	idtSetGate(24, (uint32_t)isr24, 0x08, 0x8E);
	idtSetGate(25, (uint32_t)isr25, 0x08, 0x8E);
	idtSetGate(26, (uint32_t)isr26, 0x08, 0x8E);
	idtSetGate(27, (uint32_t)isr27, 0x08, 0x8E);
	idtSetGate(28, (uint32_t)isr28, 0x08, 0x8E);
	idtSetGate(29, (uint32_t)isr29, 0x08, 0x8E);
	idtSetGate(30, (uint32_t)isr30, 0x08, 0x8E);
	idtSetGate(31, (uint32_t)isr31, 0x08, 0x8E);

	//Remaps IRQs. 
	remapIRQs();

	//Adds IRQs to IDT. 
	idtSetGate(32, (uint32_t)irq0, 0x08, 0x8E);
	idtSetGate(33, (uint32_t)irq1, 0x08, 0x8E); 
	idtSetGate(34, (uint32_t)irq2, 0x08, 0x8E); 
	idtSetGate(35, (uint32_t)irq3, 0x08, 0x8E); 
	idtSetGate(36, (uint32_t)irq4, 0x08, 0x8E); 
	idtSetGate(37, (uint32_t)irq5, 0x08, 0x8E); 
	idtSetGate(38, (uint32_t)irq6, 0x08, 0x8E); 
	idtSetGate(39, (uint32_t)irq7, 0x08, 0x8E); 
	idtSetGate(40, (uint32_t)irq8, 0x08, 0x8E); 
	idtSetGate(41, (uint32_t)irq9, 0x08, 0x8E); 
	idtSetGate(42, (uint32_t)irq10, 0x08, 0x8E); 
	idtSetGate(43, (uint32_t)irq11, 0x08, 0x8E); 
	idtSetGate(44, (uint32_t)irq12, 0x08, 0x8E); 
	idtSetGate(45, (uint32_t)irq13, 0x08, 0x8E); 
	idtSetGate(46, (uint32_t)irq14, 0x08, 0x8E); 
	idtSetGate(47, (uint32_t)irq15, 0x08, 0x8E);  

	//Loads IDTR with idtPtr. 
	idt_load(); 
}

void fault_handler(struct regs *r){
	printf("Received Interrupt: #%x\n", r->isrNum);
	while (true); 
}

void remapIRQs(){
	//Begins initialization. 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4); 

	//Sets offsets for master and slave IRQs. 
	outb(PIC1_DATA, 0x20); 
	outb(PIC2_DATA, 0x28); 

	//Connects master and slave through IRQ2. 
	outb(PIC1_DATA, 0x04); 
	outb(PIC2_DATA, 0x02); 

	//Sets PICs to 80x86 mode. 
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01); 

	//Enables all IRQs. 
	outb(PIC1_DATA, 0x0);
	outb(PIC2_DATA, 0x0); 
}

void irq_handler(struct regs *r){
	//Function pointer for handler. 
	void (*handler)(struct regs *r);

	handler = isrHandlers[r->isrNum];

	//Calls handler if valid. 
	if (handler)
		handler(r); 

	//Sends EOI request to slave PIC if necessary. 
	if (r->isrNum >= 40)
		outb(0xA0, 0x20); //Sets 5th bit in OCW2 in PIC (i.e. EOI). 

	//Sends EOI request to master PIC, this is always necessary. 
	outb(0x20, 0x20); 
}

void installISRHandler(uint32_t isr, handlerP handler){
	isrHandlers[isr] = handler;
}

void uninstallISRHandler(uint32_t isr){
	isrHandlers[isr] = 0; 
}
