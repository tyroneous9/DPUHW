//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Heap.h"
#include "Mem.h"

Heap::Heap() :
	pUsedHead(nullptr),
	pFreeHead(nullptr),
	pNextFit(nullptr),
    currNumUsedBlocks(0),
    currUsedMem(0),
    currNumFreeBlocks(0),
    currFreeMem(0)
{
}

void Heap::addFreeNode(Free* pFree) {
    assert(pFree != nullptr);
    if (this->pFreeHead == nullptr) {
        this->pFreeHead = pFree;
        pFree->pNext = nullptr;
        pFree->pPrev = nullptr;
    }
    else {
        this->pFreeHead->pPrev = pFree;
        pFree->pNext = this->pFreeHead;
        pFree->pPrev = nullptr; 
        this->pFreeHead = pFree;
    }
}

void Heap::setNextFit(Free* pFree) {
    this->pNextFit = pFree;
}

void Heap::addFreeStats(Free* pFree) {
    assert(pFree != nullptr);
    this->currNumFreeBlocks += 1;
    this->currFreeMem += pFree->mAllocSize;

}

void Heap::removeFreeNode(Free* pFree) {
    assert(pFree != nullptr);
    if(this->pFreeHead == pFree) 
        this->pFreeHead = pFree->pNext;
    if (pFree->pPrev != nullptr)
        pFree->pPrev->pNext = pFree->pNext;
    if (pFree->pNext != nullptr)
        pFree->pNext->pPrev = pFree->pPrev;
}

void Heap::removeFreeStats(Free* pFree) {
    assert(pFree != nullptr);
    this->currNumFreeBlocks -= 1;
    this->currFreeMem -= pFree->mAllocSize;
}

void Heap::addUsedNode(Used *pUsed) {
    assert(pUsed != nullptr);
    if (this->pUsedHead == nullptr) {
        this->pUsedHead = pUsed;
        pUsed->pNext = nullptr;
        pUsed->pPrev = nullptr;
    }
}

void Heap::addUsedStats(Used *pUsed) {
    assert(pUsed != nullptr);
    this->currNumUsedBlocks += 1;
    this->currUsedMem += pUsed->mAllocSize;
}

void Heap::removeUsedNode(Used* pUsed) {
    assert(pUsed != nullptr);
    if (this->pUsedHead == pUsed)
        this->pUsedHead = pUsed->pNext;
}
void Heap::removeUsedStats(Used* pUsed) {
    assert(pUsed != nullptr);
    this->currNumUsedBlocks -= 1;
    this->currUsedMem -= pUsed->mAllocSize;
}

void Heap::coalesceFreeNodes(Free* pFree) {
    assert(pFree != nullptr);
    removeFreeStats(pFree);
    uint16_t totalAllocSize = pFree->mAllocSize;
    Free* prev = pFree->pPrev;
    Free* next = pFree->pNext;
    if (prev != nullptr) {
        totalAllocSize += sizeof(Free)+prev->mAllocSize;
        removeFreeNode(prev);
        removeFreeStats(prev);
    }
    if (next != nullptr) {
        totalAllocSize += sizeof(Free) + next->mAllocSize;
        removeFreeNode(next);
        removeFreeStats(next);
    }
    pFree->mAllocSize = totalAllocSize;
    addFreeStats(pFree);
}
// --- End of File ---
