//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef TEST_JEDI_HOTCOLD_H
#define TEST_JEDI_HOTCOLD_H

class JediHotNode;
class JediRedirect;
class JediColdNode;

class TestJediHotCold
{

public:
	// -----------------------------------------------------------------
	// NO varaibles that have Count or number of nodes in list allowed
	// -----------------------------------------------------------------
	// You CANNOT add additional data to this class
	JediHotNode *pHotHead;
	JediRedirect *pRedirectHead;
	JediColdNode *pColdHead;
};

#endif

// ---  End of File ---

