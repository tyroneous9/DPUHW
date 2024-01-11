//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef SEARCH_LIST_H
#define SEARCH_LIST_H

#include "Node.h"

class AList;

class SearchList
{
public:
	// ---> CHANGE this value
	static const int CUT_OFF = 25;

public:
	// Big four
	SearchList() = delete;
	~SearchList();
	SearchList(const SearchList &) = delete;
	SearchList &operator = (const SearchList &) = delete;

	SearchList(AList *pList);

	// Accessors
	Node *GetHead() const;
	void SetHead(Node *pNode);
	int GetNumNodes() const;

	// Class methods
	int GetCutoffLength(); 

	//---------------------------------------------------------------------------------------
	// Please implement(rework) these methods (add additional methods to help if you want)
	//---------------------------------------------------------------------------------------
	void InsertionSort();
	void MergeSort();
	void MergeComboSort(int CutoffLength);
	Node* _MergeComboSort(Node* head, int cutoffLength);

private:
	// ------------------------------------------------------
	// Data - YOU CANNOT add or change data in this class
	// ------------------------------------------------------

	Node *pHead;
	int  NumNodes;
	int  mCutoffLength;
};

#endif 

// ---  End of File ---
