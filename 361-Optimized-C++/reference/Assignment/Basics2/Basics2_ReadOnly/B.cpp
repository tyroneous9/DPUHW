//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "B.h"
#include "UnitTestBufferManager.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

B::B()
	: y(33)
{
	this->buffer = new int[100];
	UnitTestBufferManager::getInstance()->increment();
}

B::~B()
{
	delete[] this->buffer;
	UnitTestBufferManager::getInstance()->decrement();
}

// --- End of File ---