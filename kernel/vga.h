/*****************************************
  Rodolfo Corona

  vga.h

  Contains declarations for the VGA class
  which is used for text based I/O.
  *****************************************/

#ifndef _VGA_H
#define _VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#include <stddef.h>
#include <stdint.h> 
#include "machine.h"

class VGA {
public:

	/* Hardware text mode color constants */
	enum vga_color{
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHT_GREY,
		DARK_GREY,
		LIGHT_BLUE,
		LIGHT_GREEN,
		LIGHT_CYAN,
		LIGHT_RED,
		LIGHT_MAGENTA,
		YELLOW,
		WHITE
	};

	//Initializes screen
	static void init(); 

	//Places a character on screen with currently set colors. 
	static void putchar(char c);

	//Sets background and foreground colors to selection. 
	static void setColor(enum vga_color fg, enum vga_color bg = BLACK); // TODO

	//Sets cursor position in text mode. 
	static void setCursor(uint8_t x, uint8_t y);
private:
	//Singleton object
	VGA(){}
	~VGA(){}

	//Current row and column where next char is to be written.
	static size_t row;
	static size_t column;
	static uint8_t color; 
	static uint16_t *screen;

	//Increments row or column
	static void incrementRow();
	static void incrementColumn();

	//Scrolls screen up by one row. 
	static void scroll();

	//Clears a row. 
	static void clearRow(uint32_t r); 
};

#endif
