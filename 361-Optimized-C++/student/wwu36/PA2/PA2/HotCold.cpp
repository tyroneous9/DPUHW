//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "hotcold.h"


HotCold::HotCold(const Bloated * const pBloated)
{
	//allocate nodes with pBloated count
	Node* bloatedCurr = pBloated->GetListHead();
	size_t count = 0;
    while(bloatedCurr != nullptr) {
		count += 1;
        bloatedCurr = bloatedCurr->pNext;
    }
	pHotHead = new HotNode[count]();
	pColdHead = new ColdNode[count]();
	bloatedCurr = pBloated->GetListHead();
	HotNode* hotCurr = pHotHead;
	HotNode* hotPrev = nullptr;
	ColdNode* coldCurr = pColdHead;
	//assign data 
	for(size_t i=0; i<count; i++) {
		coldCurr = pColdHead + i;
		*coldCurr = *bloatedCurr;
		hotCurr->key = bloatedCurr->key;
		hotCurr->pCold = coldCurr;
		hotCurr->pPrev = hotPrev;
		hotPrev = hotCurr;
		hotCurr->pNext = hotCurr+1;
		//last pNext is out of index
		if (bloatedCurr->pNext == nullptr)
			hotCurr->pNext = nullptr;
		hotCurr = hotCurr->pNext;

		bloatedCurr = bloatedCurr->pNext;
	}
}

HotCold::~HotCold()
{
	// HINT - do something here
	delete[] this->pHotHead;
	delete[] this->pColdHead;
}

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//
// Return true if you find the node
// Return the pointer in the argument list to the HotNode and ColdNode (if found)
//----------------------------------------------------------------------------------
bool HotCold::FindKey(int key, ColdNode *&pFoundColdNode, HotNode *&pFoundHotNode)
{
	HotNode* curr = pHotHead;
	while(curr != nullptr) {
		if(curr->key == key) {
			pFoundHotNode = curr;
			pFoundColdNode = curr->pCold;
			return true;
		}
		curr = curr->pNext;
	}
	
	return false;
}

HotNode *HotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---

