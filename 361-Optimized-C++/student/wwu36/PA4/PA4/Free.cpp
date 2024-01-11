//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Used.h"
#include "Free.h"
#include "Type.h"

// Add magic here
Free::Free(unsigned int BlockSize) : 
    pNext(nullptr), 
    pPrev(nullptr), 
    mAllocSize((uint16_t) BlockSize), 
    mType(Type::FREE_Type), 
    bAboveFree(false)
{

}

Free::Free(Used& rUsed) :
    pNext(nullptr),
    pPrev(nullptr),
    mAllocSize(rUsed.mAllocSize),
    mType(Type::FREE_Type),
    bAboveFree(false) 
{

}


// ---  End of File ---
