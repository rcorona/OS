/*
   Rodolfo Corona Rodriguez
   keyboard.h

   Contains declarations for keyboard functions
*/

#include "idt.h"

#define PS2_DATA 0x60
#define KEY_RELEASED 0x80

//Initializes keyboard and registers handler. 
void initKeyboard(); 

//Handles a keyboard interrupt. 
void keyboardHandler(struct regs *r); 
