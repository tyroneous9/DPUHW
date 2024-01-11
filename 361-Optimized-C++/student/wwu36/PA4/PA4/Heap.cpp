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
        setNextFit(this->pFreeHead);
    }
    else {
        //low to high address order
        Free* curr = this->pFreeHead;
        Free* prev = nullptr;
        while (curr != nullptr) {
            if (pFree < curr)
                break;
            prev = curr;
            curr = curr->pNext;
        }
        //insert behind/after curr
        if (curr == nullptr) {
            if(prev != nullptr)
                prev->pNext = pFree;
            pFree->pPrev = prev;
        }
        else if (pFree > curr) {
            pFree->pPrev = curr;
            curr->pNext = pFree;
        }
        else if(pFree < curr) {
            if (prev != nullptr)
                prev->pNext = pFree;
            pFree->pPrev = curr->pPrev;
            pFree->pNext = curr;
            curr->pPrev = pFree;
            if (curr == this->pFreeHead)
                this->pFreeHead = pFree;
        }
    }
}

void Heap::setNextFit(Free* pFree) {
    this->pNextFit = pFree;
}

Free* Heap::getNextFit() {
    return pNextFit;
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
    else {
        pUsed->pNext = pUsedHead;
        pUsed->pPrev = nullptr;
        pUsedHead->pPrev = pUsed;
        pUsedHead = pUsed;
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
    if (pUsed->pPrev != nullptr)
        pUsed->pPrev->pNext = pUsed->pNext;
    if (pUsed->pNext != nullptr)
        pUsed->pNext->pPrev = pUsed->pPrev;
}
void Heap::removeUsedStats(Used* pUsed) {
    assert(pUsed != nullptr);
    this->currNumUsedBlocks -= 1;
    this->currUsedMem -= pUsed->mAllocSize;
}


// --- End of File ---
