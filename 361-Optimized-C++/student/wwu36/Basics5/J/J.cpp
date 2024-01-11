//----------------------------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "J.h"

// ----------------------------------------------------------------------
//
// J - Project
//
// Rules: Fix the code to correctly print the predicted output
//        no memory leak
//
// ----------------------------------------------------------------------

Dog::Dog(int val)
{
	this->val = val;
	pVal = &this->val;
}

Dog::~Dog()
{
	//delete pVal;
}

// Do not modify this method
int Dog::GetVal(Dog d)
{
	return *(d.pVal);
}

// End of File
