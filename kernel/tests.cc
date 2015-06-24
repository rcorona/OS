/*
Tests.cc
Rodolfo Corona Rodriguez

Implementation for kernel testing functions. 
*/

#include "tests.h"

void Tests::testHeap(){
	printf("Testing the heap...\n\n");
	
	//Tests malloc by itself.
	printf("Test1: Malloc by itself...\n");
	
	int *numP1 = (int *)malloc(sizeof(int));
	int *numP2 = new int; 
	
	char *charP = new char[4];
	charP[0] = 'P';
	charP[1] = 'A';
	charP[2] = 'S';
	charP[3] = 'S';
	
	if (numP1 == numP2)
		PANIC("Heap assigned same address to two pointers!!!");

	printf("Status: %sED\n\n", charP);
	
	//Tests free by itself. 
	printf("Test2: Free by itself...\n");
	
	free(numP1);
	delete numP2;
	delete [] charP; 
	
	if (!(numP1 == malloc(sizeof(int))))
		printf("First assignment on newly freed heap not same as last time, is that expected?\n\n");
	
	
	//Tests coalescing
	printf("Test3: Coalescing...\n");
	
	delete numP1;

	numP1 = new int; 
	numP2 = new int;
	int* numP3 = new int;
	
	printf("Current heap:\n");
	Heap::printHeap();
	
	printf("Freeing middle:\n");
	delete numP2; 
	Heap::printHeap();
	
	printf("Freeing right for right coalesce:\n");
	delete numP3;
	Heap::printHeap();
	
	printf("Freeing left for left coalesce:\n");
	delete numP1;
	Heap::printHeap(); 
}
