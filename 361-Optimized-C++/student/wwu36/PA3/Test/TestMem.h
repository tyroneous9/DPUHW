//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef TEST_MEM_H
#define TEST_MEM_H

#include "Type.h"
#include "Mem.h"
class Heap;

//--------------------------------
//    DO NOT MODIFY this File
//--------------------------------

struct TestMem
{
	Heap *poHeap;
	Mem::Guard type;
	void *poRawMem;
};

#endif

// ---  End of File ---
