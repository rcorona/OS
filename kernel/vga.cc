/***************************************
  Rodolfo Corona
  vga.cc

  Contains definitions for the VGA class
  ***************************************/

#include "vga.h"

size_t VGA::row = 0;
size_t VGA::column = 0;
uint8_t VGA::color = VGA::WHITE | (VGA::BLACK << 4);
uint16_t *VGA::screen = (uint16_t *)0xB8000; 

void VGA::putchar(char c){
	switch (c){
		case '\n':
			incrementRow();
			column = 0; 
			break;

		default:
			screen[row * VGA_WIDTH + column] = (uint16_t)c | (color << 8);
			incrementColumn(); 
			break;

		// TODO add more cases (Tab etc.). 
	}

	//TODO make faster by waiting til end of input to update. 
	//i.e. until after done with printf or prints etc. 
	setCursor(column, row);
}

void VGA::init(){
	// TODO technically incorrect count, although below is a fix. 
	for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
		putchar(' '); 

	row = 0;
	column = 0; 
}

void VGA::setColor(enum vga_color fg, enum vga_color bg){
	// TODO Change to actually set color. Delete code below. 
	fg = bg; 
	bg = fg; 
}

void VGA::incrementRow(){
	if (++row == VGA_HEIGHT)
		scroll();
}

void VGA::incrementColumn(){
	if (++column == VGA_WIDTH){
		row = 0;

		incrementRow(); 
	}
}

void VGA::setCursor(uint8_t x, uint8_t y){
	uint16_t position = (y * VGA_WIDTH) + x; 

	//Tells VGA board we are setting high byte and sends it. 
	outb(0x3D4, 14);
	outb(0x3D5, position >> 8);

	//Does same for low byte. 
	outb(0x3D4, 15);
	outb(0x3D5, position); 
}

void VGA::scroll(){
	uint16_t oldIndex, newIndex; 

	for (int y = 1; y < VGA_HEIGHT; y++){
		for (int x = 0; x < VGA_WIDTH; x++){
			newIndex = ((y - 1) * VGA_WIDTH) + x; 
			oldIndex = (y * VGA_WIDTH) + x; 

			//Scrolls up one row. 
			screen[newIndex] = screen[oldIndex]; 
		}
	}

	clearRow(VGA_HEIGHT - 1); 

	setCursor(column, --row);
}

void VGA::clearRow(uint32_t r){
	for (int x = 0; x < VGA_WIDTH; x++){
		uint32_t index = (r * VGA_WIDTH) + x;

		screen[index] = (uint16_t)' ' | (color << 8); 
	}
}
