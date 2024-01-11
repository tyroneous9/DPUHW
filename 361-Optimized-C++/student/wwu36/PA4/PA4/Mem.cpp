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

void Mem::setSecretPtr(Free* pFree) {
	Used* pBelow = (Used*)((char*)pFree + sizeof(Free) + pFree->mAllocSize);
	if (pBelow->mType == Type::USED_Type)
		pBelow->bAboveFree = true;
	SecretPtr* pSecret = (SecretPtr*)pBelow - 1;
	pSecret->pFree = pFree;
}

Free* getFreeAbove(Used* pUsed) {
	SecretPtr* pSecret = (SecretPtr*)pUsed - 1;
	return pSecret->pFree;
}

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
	setSecretPtr(pFree);
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
	// search for suitable free block
	assert(this->poHeap != nullptr);
	Free* nextFit = this->poHeap->getNextFit();
	Free* pFree = nextFit;
	while(pFree != nullptr) {
		if(pFree->mAllocSize >= _size)
			break;
		pFree = pFree->pNext;
	}
	// loop back if no fits
	if (pFree == nullptr) {
		pFree = this->poHeap->pFreeHead;
		while (pFree != nextFit) {
			if (pFree->mAllocSize >= _size)
				break;
			pFree = pFree->pNext;
		}
		if (pFree == nextFit)
			pFree = nullptr;
	}
	
	// allocate
	if(pFree != nullptr) {
		if(pFree->mAllocSize == _size) {
			//perfect fit
			Used* pBelow = (Used*)((char*)pFree + sizeof(Free) + pFree->mAllocSize);
			if (pBelow->mType == Type::USED_Type)
				pBelow->bAboveFree = false;
			this->poHeap->removeFreeNode(pFree);
			this->poHeap->removeFreeStats(pFree);
			this->poHeap->setNextFit(this->poHeap->pFreeHead);
		}
		else {
			// subdivide for leftover memory
			void* pRemaining = (void*)((char*)pFree + (_size + sizeof(Free)));
			unsigned int remainingSize = (unsigned int)(pFree->mAllocSize - (_size+sizeof(Free)));
			Free* newFree = new(pRemaining) Free(remainingSize);
			this->poHeap->removeFreeNode(pFree);
			this->poHeap->removeFreeStats(pFree);
			this->poHeap->setNextFit(newFree);
			this->poHeap->addFreeNode(newFree);
			this->poHeap->addFreeStats(newFree);
			setSecretPtr(newFree);
			pFree->mAllocSize = (uint16_t)_size;
		}
		// convert to used
		Used* pUsed = new(pFree) Used(*pFree);
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
	Used* pUsed = (Used*)data - 1;
	this->poHeap->removeUsedNode(pUsed);
	this->poHeap->removeUsedStats(pUsed);

	//init for coalescence
	uint16_t totalAllocSize = pUsed->mAllocSize;
	Free* pNewFree;
	Free* pFreeBelow = nullptr;
	Free* pFreeAbove = nullptr;
	Free* prev = nullptr;
	Free* next = nullptr;

	// check below
	Used* pUnknownBelow = (Used*)((char*)pUsed + sizeof(Used) + pUsed->mAllocSize);
	if (pUnknownBelow->mType == Type::FREE_Type) {
		pFreeBelow = (Free*)pUnknownBelow;
		prev = pFreeBelow->pPrev;
		next = pFreeBelow->pNext;
		totalAllocSize += sizeof(Free) + pFreeBelow->mAllocSize;
		this->poHeap->removeFreeNode(pFreeBelow);
		this->poHeap->removeFreeStats(pFreeBelow);
	}

	// check above
	if (pUsed->bAboveFree == true) {
		pFreeAbove = ((SecretPtr*)pUsed-1)->pFree;
		prev = pFreeAbove->pPrev;
		next = pFreeAbove->pNext;
		totalAllocSize += sizeof(Free) + pFreeAbove->mAllocSize;
		this->poHeap->removeFreeNode(pFreeAbove);
		this->poHeap->removeFreeStats(pFreeAbove);
		pUsed = (Used*)pFreeAbove;
	}

	//allocate Free
	pNewFree = new(pUsed) Free(totalAllocSize);
	this->poHeap->addFreeStats(pNewFree);
	setSecretPtr(pNewFree);

	// find address order using adjacent info
	if (pFreeBelow == nullptr && pFreeAbove == nullptr) {
		this->poHeap->addFreeNode(pNewFree);
		return;
	}
	// relink to pNewFree
	else {
		if (this->poHeap->pFreeHead == nullptr) {
			this->poHeap->pFreeHead = pNewFree;
			this->poHeap->setNextFit(pNewFree);
		}
		if (prev != nullptr)
			prev->pNext = pNewFree;
		else
			this->poHeap->pFreeHead = pNewFree;
		if (next != nullptr)
			next->pPrev = pNewFree;
		pNewFree->pPrev = prev;
		pNewFree->pNext = next;
	}
	
} 
// --- End of File ---
 