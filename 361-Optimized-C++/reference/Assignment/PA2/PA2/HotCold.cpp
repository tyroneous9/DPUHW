//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "hotcold.h"

HotCold::HotCold(const Bloated * const pBloated)
{
	AZUL_REPLACE_ME(pBloated);
}

HotCold::~HotCold()
{
	// HINT - do something here
	AZUL_INSERT_CODE_HERE;
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
	AZUL_REPLACE_ME(key);
	AZUL_REPLACE_ME(pFoundColdNode);
	AZUL_REPLACE_ME(pFoundHotNode);
	return false;
}

HotNode *HotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---

