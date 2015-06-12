/*
   Rodolfo Corona Rodriguez
   pit.cc

   Contains definitions for PIT functions. 
*/

#include "pit.h"

uint32_t ticks = 0;
uint32_t seconds = 0; 

void initPIT(uint32_t hz){
	//Registers PIT handler as callback function for IRQ0. 
	installISRHandler(IRQ0, &PITHandler); 

	uint32_t divisor = PIT_IN_FREQ / hz;

	//Sets PIT channel 0 to Square Wave Mode. 
	outb(PIT_COMMAND, SQR_WAVE | ACCESS_LO_HI);

	//Sends divisor's low byte. 
	outb(CH0_DATA, divisor & 0xFF);

	//Sends high byte. 
	outb(CH0_DATA, (divisor >> 8) & 0xFF); 
}

void PITHandler(struct regs *r){
	if (false)//! (ticks++ % 100))
		printf("%lu seconds have passed...\n", seconds++); 

	(void)r; //TODO Remove once r is actually used. 
}
