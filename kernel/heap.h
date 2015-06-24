/*
   Rodolfo Corona Rodriguez
   heap.h

   Contains declarations for the Heap abstract class and its
   derived classes. 
*/

#ifndef _HEAP_H
#define _HEAP_H

#include <stddef.h>
#include "stdio.h"

//Beginning of main heap (if there are multiple). 
#define HEAP_START 0x100000

//Size of main heap (if there are multiple). 
#define HEAP_SIZE 0x300000

//End of heap. 
#define HEAP_END HEAP_START + HEAP_SIZE

//Minimum size of data part of block in bytes. 
#define MIN_BLCK_DATA 4

//Error codes
#define HDR_FTR_MISMATCH 1
#define BLCK_SZ_MISMATCH 2

//General malloc and free functions. Will call
//pertaining function using current heap.
//TODO possibly move this to cstdlib. 
void *malloc(size_t size); 
void free(void *ptr); 

//TODO add functionality for picking type of heap. 

/*Abstract base Heap class*/
class Heap_Base{
public:
	//Takes a start address and a size in bytes. 
	Heap_Base(void *baseAddr, size_t bytes) : base(baseAddr), size(bytes) {}

	~Heap_Base(); 

	/*Allocates a block of at least size bytes of memory and
	returns a pointer to it. In case of failure, returns NULL*/
	virtual void *malloc(size_t size) = 0;

	/*Frees allocated block of memory pointed at by ptr. 
	  If ptr is NULL, then does nothing. If ptr does not point
	  to a valid block, function will fail (i.e. system crash
	  at kernel level, or process getting killed at user).*/ 
	virtual void free(void *ptr) = 0; 

	/* Performs a "sanity" check on a block to make sure
	   that it's header and footer match and that the size
	   of the block is correct 

	   optional calling function name may be inputted*/
	virtual uint32_t sanity(void *block, const char *function = "") = 0;
	
	//Visually prints the heap. 
	virtual void printHeap() = 0;

private:
	void *base; 
	size_t size; 
};

//Singleton class used as interface. 
class Heap{
public:
	//TODO add arg for type of heap to be used. 
	static void init(void *baseAddr, size_t bytes);

	static void *malloc(size_t size); 

	static void free(void *ptr); 
	
	static void printHeap(); 

private:
	//Singleton class. 
	Heap(); 
	~Heap(); 

	//Points to current heap being used. 
	static Heap_Base *heap; 
};

//A first fit heap. 
class FF_Heap : public Heap_Base{
public:
	FF_Heap(void *baseAddr, size_t bytes);  
	~FF_Heap(); 

	void *malloc(size_t size); 
	void free(void *ptr); 

	uint32_t sanity(void *block, const char *function = ""); 
	
	void printHeap(); 

private:
	struct header{
		uint32_t size;
		bool free; 
	};

	struct footer{
		uint32_t size;
		bool free; 
	};

	//Typedefs for header and footer.
	typedef struct header hdr_t; 
	typedef struct footer ftr_t; 

	typedef hdr_t* hdrP; 
	typedef ftr_t* ftrP;  

	//Pointer to the first block. 
	void *firstBlock; 

	/*Creates a free block with the given size and start addres,
	  then returns a pointer to it. NOTE: size should include hdr & ftr*/
	void *makeBlock(uint8_t *startAddr, size_t size); 
	
	//Returns a footer pointer given a block's starting address (start for data that is). 
	ftrP getFooter(void *block);

	//Returns a header pointer given a block's starting address. 
	hdrP getHeader(void *block); 

	//Determines if a block is free or not. 
	bool isFree(void *block);

	//Determines if block will fit desired size in bytes. 
	bool isFreeFit(void *block, size_t size);

	//Returns next block. Will wrap and return firstBlock. 
	void *nextBlock(void *block); 

	//Returns previous block. Will return firstBlock if no previous blocks found. 
	void *prevBlock(void *block); 

	//Splits block into two blocks if possible. 
	void splitBlock(void *block, size_t size); 

	//Coalesces block on left with one on right. 
	void coalesce(void *left, void *right); 
};

#endif
