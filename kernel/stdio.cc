/********************************************
  Rodolfo Corona
  stdio.cc

  Contains definitions for the functions
  declared in stdio.h
  *******************************************/

#include "stdio.h"

void putchar(char c){
	VGA::putchar(c); 
}

void puts(const char *str){
	uint32_t index = 0;

	while (str[index])
		VGA::putchar(str[index++]); 
}

void printf(const char *str, ...){
	int index = 0;
	va_list args; 

	va_start(args, str); 

	//TODO add more cases/functionality until full printf specs are met. 

	while (str[index]){
		if (str[index] == '%'){
			switch (str[++index]){
				case 'd':
					putdec(va_arg(args, int)); 
					break;

				case 'i':
					putdec(va_arg(args, int));
					break;

				case 'x':
					puthex(va_arg(args, unsigned int)); 
					break;

				case 'c':
					putchar(va_arg(args, int)); 
					break;

				case 's':
					puts(va_arg(args, const char *)); 
					break;

				case 'l':
					switch (str[++index]){
						case 'u':
							putdec(va_arg(args, long unsigned int));
							break;

						case 'd':
							putdec(va_arg(args, long int)); 
							break;

						case 'i':
							putdec(va_arg(args, long int)); 
							break;

						case 'x':
							puthex(va_arg(args, long unsigned int)); 
							break;
					}

					break;

				case 'z':
					switch (str[++index]){
						case 'd':
							putdec(va_arg(args, size_t));
							break;

						case 'i':
							putdec(va_arg(args, size_t));
							break;

						case 'u':
							putdec(va_arg(args, size_t));
							break;
					}

					break;

				default:
					break; // DO NOTHING
			}

			index++; 
		}
		else
			putchar(str[index++]); 
	}

	va_end(args); 
}

void puthex(int num){
	puts("0x"); 

	char mask = 0x0F; 
	int index = 28; 

	//Gets rid of leading 0's 
	while (index > 0 && !(num & (mask << index)))
		index -= 4;

	int digit;
	int ascii; 

	while (index >= 0){
		digit = (num >> index) & mask; 
		ascii = (digit >= 10) ? 55 : 48; 

		//Prints hex digit
		putchar(digit + ascii); 

		index -= 4; 
	}
}

void putdec(int num){
	if (num == 0){
		putchar(48);

		return;
	}


	int place = 1000000000; 

	//Deals with negative case. 
	if ((num >> 28) & 0x80){
		putchar('-'); 
		place *= -1;  
	}

	//Gets rid of trailing 0's. 
	while (!(num / place))
		place /= 10; 

	while (place){
		putchar((num / place) + 48); 

		num %= place; 
		place /= 10;
	}
}
