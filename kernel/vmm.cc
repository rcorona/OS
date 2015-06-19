/*
vmm.cc
Rodolfo Corona Rodriguez

Contains definitions for virtual memory functions and objects.
*/

#include "vmm.h"
#include "stdio.h"

uint8_t *PhysMem::frames = 0; 
uint32_t PhysMem::nFrames = 0;

void PhysMem::init(uint32_t start, uint32_t end){
	if (start < 0 || end < start)
		PANIC("Given range doesn't make sense!");
	
	if (start % ALIGNMENT)
		PANIC("Start address not page aligned!");
	
	nFrames = (end - start) / ALIGNMENT; 
	nFrames += ((end - start) % ALIGNMENT) ? 1 : 0; 
	
	uint32_t bitMapFrames = nFrames / ALIGNMENT; 
	bitMapFrames += (nFrames % ALIGNMENT) ? 1 : 0; 
	
	frames = (uint8_t *)start;
	uint32_t frameNum = 0; 
	
	//TODO consider using memset or some other more efficient mechanism for initializing bitmap. 
	
	while (frameNum < bitMapFrames){
		*(frames + frameNum) = 1;
		frameNum++; 
	}
	
	while (frameNum < nFrames){
		*(frames + frameNum) = 0;
		frameNum++;
	}
}

uint32_t PhysMem::alloc(){
	uint32_t frameNum = 0; 
	
	//TODO Consider making this more efficient. 
	
	while (*(frames + frameNum))
		frameNum++; 
	
	return (uint32_t)frames + (frameNum * ALIGNMENT);
}

void PhysMem::free(uint32_t frame){
	if (frame < (uint32_t)frames)
		PANIC("Trying to free frame out of bounds!");
	
	if (frame % ALIGNMENT)
		PANIC("Trying to free a frame at an address that's not aligned!");
	
	frameNum = (frame - (uint32_t)frames) / ALIGNMENT; 
	
	*(frames + frameNum) = 0; 
}