/*
vmm.h
Rodolfo Corona Rodriguez

Contains declarations for virtual memory functions and objects
*/

#ifndef _VMM_H
#define _VMM_H

class PhysMem{
public:
	//Bitmap for all the frames. 
	static uint8_t *frames; 
	
	//Keeps track of the number of frames. 
	static uint32_t nFrames; 
	
	//Alignment value for frames. 
	static constexpr uint32_t ALIGNMENT = 0x1000;
	
	//Initializes bitmap for use with given range. 
	static void init(uint32_t start, uint32_t end);
	
	//Allocates a frame and returns its physical address. 
	static uint32_t alloc();
	
	//Frees the given frame. 
	static void free(uint32_t frame);
	
private:
};

#endif