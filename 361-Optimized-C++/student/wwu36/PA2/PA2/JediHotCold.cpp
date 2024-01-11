//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "JediHotCold.h"
#include "JediRedirect.h"

JediHotCold::JediHotCold(const Bloated * const pBloated)
{
	//allocate nodes with pBloated count
	Node* bloatedCurr = pBloated->GetListHead();
	size_t count = 0;
	while (bloatedCurr != nullptr) {
		count += 1;
		bloatedCurr = bloatedCurr->pNext;
	}
	pHotHead = new JediHotNode[count / JediHotNode::KeyMax]();
	pColdHead = new JediColdNode[count]();
	bloatedCurr = pBloated->GetListHead();
	JediHotNode* hotCurr = pHotHead;
	JediHotNode* hotPrev = nullptr;
	JediColdNode* coldCurr = pColdHead;
	//assign data 
	for (size_t i=0, keyCount=0; i<count; i++, keyCount++) {
		//hotnode assign
		if (keyCount == 8) {
			keyCount = 0;
			hotCurr->pPrev = hotPrev;
			hotPrev = hotCurr;
			hotCurr->pNext = hotCurr + 1;
			hotCurr = hotCurr->pNext;
		}
		hotCurr->key[keyCount] = bloatedCurr->key;
		//coldnode assign
		coldCurr = pColdHead + i;
		*coldCurr = *bloatedCurr;
		hotCurr->pRedirect->pCold[keyCount] = coldCurr;
		bloatedCurr = bloatedCurr->pNext;
	}
	hotCurr->pNext = nullptr;
}

JediHotCold::~JediHotCold()
{
	// HINT - do something here

	delete[] pHotHead;
	delete[] pColdHead;
}

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//
// Return true if you find the node
// Return the pointer in the argument list to the HotNode and ColdNode (if found)
//----------------------------------------------------------------------------------
bool JediHotCold::FindKey(int key, JediColdNode *&pFoundColdNode, JediHotNode *&pFoundHotNode)
{
	JediHotNode* curr = pHotHead;
	while (curr != nullptr) {
		for (int i = 0; i < JediHotNode::KeyMax; i++) {
			if (curr->key[i] == key) {
				pFoundHotNode = curr;
				pFoundColdNode = curr->pRedirect->pCold[i];
				return true;
			}
		}
		curr = curr->pNext;
	}
	return false;
}

JediHotNode *JediHotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---

