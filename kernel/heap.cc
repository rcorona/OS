/*
   Rodolfo Corona Rodriguez
   heap.cc

   Contains definitions for Heap classes and pertaining funcitons. */

#include "heap.h"

Heap_Base *Heap::heap = 0; 

/* PLACEMENT NEW */


void *operator new(size_t size, void *ptr){
	return ptr; 
}


/* STANDARD HEAP OPERATIONS */


void *malloc(size_t size){
	return Heap::malloc(size); 
}

void free(void *ptr){
	Heap::free(ptr); 
}


/* HEAP INTERFACE FUNCTIONS */


void Heap::init(void *baseAddr, size_t size){
	heap = new(baseAddr) FF_Heap(baseAddr, size);  
}

void *Heap::malloc(size_t size){
	return heap->malloc(size); 
}

void Heap::free(void *ptr){
	heap->free(ptr); 
}


/* First Fit Heap implementation */


FF_Heap::FF_Heap(void *baseAddr, size_t size) : Heap_Base(baseAddr, size){
	//Heap object is placed at base addr.
	//So first block must be placed after. 
	uint32_t firstBlckAddr = (uint32_t)baseAddr + sizeof(FF_Heap);
	size_t firstBlckSize = size - sizeof(FF_Heap);

	firstBlock = makeBlock((uint8_t *)firstBlckAddr, firstBlckSize);

	hdrP hdr = (hdrP)getHeader(firstBlock);

	printf("Created first block with address: %x, size: %d\n", (uint32_t)firstBlock, hdr->size); 

	printf("sizeof heap: %x sizeof hdr: %x, sizeof footer: %x\n", sizeof(FF_Heap), sizeof(hdr_t), sizeof(ftr_t)); 
}

void *FF_Heap::makeBlock(uint8_t *startAddr, size_t size){
	//Calculates actual block size. 
	uint32_t blckSz = size - sizeof(hdr_t) - sizeof(ftr_t); 
	
	//Creates header. 
	hdrP hdr = (hdrP)startAddr; 
	hdr->size = blckSz;
	hdr->free = true; 

	void *block = (void *)(startAddr + sizeof(hdr_t)); 

	//Creates footer. 
	ftrP ftr = getFooter(block); 
	ftr->size = blckSz;
	ftr->free = true; 

	//Performs sanity check on block. 
	sanity(block); 

	//Returns newly created block. 
	return block; 
}

FF_Heap::hdrP FF_Heap::getHeader(void *block){
	return (hdrP)((uint8_t *)block - sizeof(hdr_t)); 
}

FF_Heap::ftrP FF_Heap::getFooter(void *block){
	uint8_t *addr = (uint8_t *)block - sizeof(hdr_t); 
	hdrP hdr = (hdrP)addr; 

	return (ftrP)(addr + sizeof(hdr_t) + hdr->size); 
}

void FF_Heap::sanity(void *block){
	hdrP hdr = getHeader(block);
	ftrP ftr = getFooter(block); 

	if (hdr->free != ftr->free || hdr->size != ftr->size)
		PANIC("Header and footer don't match!!!")

	//Gets actual size of block and compares it to value in hdr. 
	uint32_t blockSize = (uint32_t)ftr - ((uint32_t)hdr + sizeof(hdr_t));  

	if (blockSize != hdr->size)
		PANIC("Actual block size not equal to value in header!!!");
}

bool FF_Heap::isFree(void *block){
	return getHeader(block)->free; 
}

bool FF_Heap::isFreeFit(void *block, size_t size){
	hdrP hdr = getHeader(block);

	return (hdr->free && hdr->size <= size); 
}

void *FF_Heap::nextBlock(void *block){
	hdrP hdr = getHeader(block); 

	//Calculates difference between start of block and next one. 
	uint32_t diff = hdr->size + sizeof(hdr_t) + sizeof(ftr_t); 

	void *nextBlock = (void *)((uint8_t *)block + diff); 
	bool wrap = (uint32_t)nextBlock > HEAP_END; 

	//Returns nextBlock or firstBlock if wrapping is necessary. 
	return wrap ? firstBlock : nextBlock; 
}

void FF_Heap::splitBlock(void *block, size_t size){
	hdrP hdr = getHeader(block); 

	//Gets block size specifications. 
	size_t metaData = sizeof(hdr_t) + sizeof(ftr_t); 
	size_t blockSize = hdr->size + metaData;  
	size_t requestSize = size + metaData;
	size_t minBlockSize = MIN_BLCK_DATA + metaData;

	//Determines if there's enough space to split block in two. 
	bool canSplit = blockSize - requestSize >= minBlockSize; 

	//Splits block if able. 
	if (canSplit){
		//Makes requested block. 
		void *newBlock = makeBlock((uint8_t *)hdr, requestSize);

		//Ensures new block is at same address. 
		if (newBlock != block)
			PANIC("Split created block at different address!!!"); 

		uint8_t *nextStart = (uint8_t *)getFooter(block) + sizeof(ftr_t); 

		//Makes second block out of split. 
		makeBlock(nextStart, blockSize - requestSize); 
	}
}

void *FF_Heap::malloc(size_t size){
	void *block = firstBlock; 

	//Rounds size up to a multiple of 4.
	size_t extraBytes = 4 - (size % 4);
	size_t actualSize = size + extraBytes; 

	//Gets first free fitting block. 
	while (!isFreeFit(block, actualSize)){
		block = nextBlock(block); 
	
		//Search wrapped without finding a block. 
		if (block == firstBlock)
			PANIC("No free blocks of given size!!!"); 
	}

	//Splits block if possible. 
	splitBlock(block, actualSize); 

	return block; 
}

void FF_Heap::free(void *ptr){
	// TODO
}
