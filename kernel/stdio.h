/*******************************************
  Rodolfo Corona
  stdio.h

  contains forward declarations for standard
  I/O functions.
  ******************************************/

#ifndef STDIO_H
#define STDIO_H

#include "vga.h"
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

//For debugging. Will halt the system with message. 
#define PANIC(...) {printf("PANIC: "); printf(__VA_ARGS__); while (true);}

void putchar(char c);
void puts(const char *str); 
void puthex(int num);
void putdec(int num); 

//GCC will check for correct number of args. 
void printf(const char *str, ...) __attribute__ ((format (printf, 1, 2))); 

#endif
