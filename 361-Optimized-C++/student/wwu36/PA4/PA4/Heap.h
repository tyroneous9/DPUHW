//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef HEAP_H
#define HEAP_H

#include "Used.h"
#include "Free.h"

class Heap
{
public:
	// Big four
	Heap();
	Heap(const Heap&) = delete;
	Heap& operator =(const Heap&) = delete;
	~Heap() = default;

public:
	void addFreeNode(Free* pFree);
	void setNextFit(Free* pFree);
	void addFreeStats(Free* pFree);
	void removeFreeNode(Free* pFree);
	void removeFreeStats(Free* pFree);
	void addUsedNode(Used *pUsed);
	void addUsedStats(Used *pUsed);
	void removeUsedNode(Used* pUsed);
	void removeUsedStats(Used* pUsed);
	Free* getNextFit();

public:
	// allocation links
	Used	    *pUsedHead;
	Free	    *pFreeHead;

	// Next fit allocation strategy
	Free        *pNextFit;

	uint32_t    currNumUsedBlocks;   // number of current used allocations
	uint32_t    currUsedMem;         // current size of the total used memory

	uint32_t    currNumFreeBlocks;   // number of current free blocks
	uint32_t    currFreeMem;         // current size of the total free memory

	uint32_t    pad;
};

#endif 

// --- End of File ---
