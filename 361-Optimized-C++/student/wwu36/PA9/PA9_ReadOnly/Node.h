//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef NODE_H
#define NODE_H

struct Node
{	
public:
	Node();
	Node(const Node &) = delete;
	Node &operator = (const Node &) = delete;
	~Node();
	
// ---------------------
// Data:
// ---------------------
public:
	Node *pNorth;
	Node *pSouth;
	Node *pEast;
	Node *pWest;
};

#endif

// ---  End of File ---
