//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Mem.h"
#include "Heap.h"
#include "Type.h"

// To help with coalescing... not required
struct SecretPtr
{
	Free *pFree;
};

// ----------------------------------------------------
//  Initialized the Memory block:
//  Update the Heap
//  Create a free block
//  Heap structure links to free hdr
//-----------------------------------------------------
void Mem::initialize()
{
	// location of each block
	Heap* pA = this->poHeap;
	Heap* pB = pA + 1;
	Free* pC = (Free*)pB + 1;
	void* pD = (void*)((char*)pA + Mem::TotalSize);
	unsigned int FreeSize = (unsigned int) ((char*)pD - (char*)pC);
	//allocate free block to heap
	Free* pFree = new(pB) Free(FreeSize);
	this->poHeap->addFreeNode(pFree);
	this->poHeap->setNextFit(pFree);
	this->poHeap->addFreeStats(pFree);
}

// ----------------------------------------------------
//  Do your Magic here:
//  Find a free block that fits
//  Change it to used (may require subdivision)
//  Correct the heap Links (used,free) headers 
//  Update stats
//  Return pointer to block
//-----------------------------------------------------
void *Mem::malloc( const uint32_t _size )
{
	Used *pUsed = nullptr;
	// search for suitable free block
	assert(this->poHeap != nullptr);
	Free* pFree = this->poHeap->pFreeHead;
	while(pFree != nullptr) {
		if(pFree->mAllocSize >= _size)
			break;
		pFree = pFree->pNext;
	}
	// allocate
	if(pFree != nullptr) {
		if(pFree->mAllocSize == _size) {
			//perfect fit
			this->poHeap->removeFreeNode(pFree);
			this->poHeap->removeFreeStats(pFree);
			this->poHeap->setNextFit(this->poHeap->pFreeHead);
		}
		else {
			// subdivide for leftover memory
			void* pRemaining = (void*)((char*)pFree + (_size + sizeof(Free)));
			unsigned int remainingSize = (unsigned int)(pFree->mAllocSize - (_size+sizeof(Free)));
			Free* newFree = new(pRemaining) Free(remainingSize);
			this->poHeap->addFreeNode(newFree);
			this->poHeap->addFreeStats(newFree);
			this->poHeap->removeFreeNode(pFree);
			this->poHeap->removeFreeStats(pFree);
			this->poHeap->setNextFit(this->poHeap->pFreeHead);
			pFree->mAllocSize = (uint16_t)_size;
		}
		// convert to used
		pUsed = new(pFree) Used(*pFree);
		this->poHeap->addUsedNode(pUsed);
		this->poHeap->addUsedStats(pUsed);
		// return mem not including header
		return pUsed+1;
	}
	return nullptr;
}	

// ----------------------------------------------------
//  Do your Magic here:
//  Return the free block to the system
//  May require Coalescing
//  Correct the heap Links (used,free) headers 
//  Update stats
//-----------------------------------------------------
void Mem::free( void * const data )
{
	// remove used
	assert(data != nullptr);
	assert(this->poHeap != nullptr);
	Used* pUsed = (Used*) ((char*)data - sizeof(Used));
	this->poHeap->removeUsedNode(pUsed);
	this->poHeap->removeUsedStats(pUsed);
	// convert to free and coalesce
	Free* pFree = new(pUsed) Free(*pUsed);
	this->poHeap->addFreeNode(pFree);
	this->poHeap->addFreeStats(pFree);
	this->poHeap->setNextFit(this->poHeap->pFreeHead);
	this->poHeap->coalesceFreeNodes(pFree);
} 
// --- End of File ---
 