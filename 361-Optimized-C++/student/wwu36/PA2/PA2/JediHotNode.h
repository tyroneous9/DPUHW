//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef JEDI_HOT_NODE_H
#define JEDI_HOT_NODE_H

class JediRedirect;

class JediHotNode
{
public:
	static const unsigned int KeyMax = 8;

public:
	JediHotNode();
	~JediHotNode();
	// You CANNOT add additional data to this class
	JediHotNode   *pNext;
	JediHotNode   *pPrev;
	int		       key[KeyMax];
	JediRedirect   *pRedirect;
};

#endif

// ---  End of File ---

