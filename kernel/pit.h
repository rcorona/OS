/*
   pit.h
   Contains functions related to the PIT. 
*/

#ifndef _PIT_H
#define _PIT_H

#include "machine.h"
#include "idt.h"
#include "stdio.h"

#define CH0_DATA 0x40		//Data port for PIT channel 0. 
#define PIT_COMMAND 0x43	//Command port for PIT. 

//Frequency for PIT in ms. Change this value to change PIT freq.
//NOTE: Everything is calculated with integers. If freq. in 
//ms does not divide 1000, then accuracy will be lost. 
#define PIT_FREQ_MILL 10

#define PIT_FREQ (1000 / PIT_FREQ_MILL)	//PIT freq. in Hz. 
#define PIT_IN_FREQ	1193180		//The PIT's input frequency in Hz. 

#define SQR_WAVE 0x3 << 1		//Square Wave mode.

//Tells PIT to expect low and high bytes for 16 bit divisor. 
#define ACCESS_LO_HI 0x3 << 4	

//Initializes PIT to fire at hz rate. 
void initPIT(uint32_t hz); 

//Handles a timer interrupt. 
void PITHandler(struct regs *r); 

#endif
