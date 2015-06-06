/*
   Rodolfo Corona Rodriguez
   keyboard.cc

   Contains definitions for keyboard functions. 
*/

#include "keyboard.h"

unsigned char kbdUS[58] = {
	0,	//0th key not used. 
	27, //ESC
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=',
	0, //BACKSPACE
	0, //TAB
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
	'[', ']',
	0, //ENTER
	0, //L_CTRL && R_CTRL
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
	'`', 0, //L SHIFT
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
	0, //R SHIFT
	0, //PRISC
	0, //L ALT && R ALT
	' ' //SPACE
};

void initKeyboard(){
	installISRHandler(IRQ1, &keyboardHandler); 
}

void keyboardHandler(struct regs *r){
	uint8_t scancode = inb(PS2_DATA);

	if (scancode & KEY_RELEASED){
		// TODO Key released. 
	}
	else{
		if (scancode < 58)
			putchar(kbdUS[scancode]); 
		else
			printf("Key %d pressed.\n", scancode); 
	}
}
