//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Free.h"
#include "Used.h"

// Add code here
Used::Used(Free& rFree) :
    pNext(nullptr),              
    pPrev(nullptr),    
    mAllocSize(rFree.mAllocSize),
    mType(Type::USED_Type),  
    bAboveFree(false)
{
    
}

// ---  End of File ---

