//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef FREE_H
#define FREE_H

#include "Type.h"

class Used;

class Free
{
public:
    // ---------------------------------------------------------
    // Do not reorder, change or add data fields
    //     --> any changes to the data... 0 given to the assignment
    // You can add methods if you wish
    // ---------------------------------------------------------

    Free *pNext;              // next free Type
    Free *pPrev;              // prev free Type  
    uint16_t   mAllocSize;    // size (16 bit)
    Type       mType;         // Type type 
    bool       bAboveFree;    // Type above is free (T/F)
                                         
    Free() = default;      
    Free(const Free&) = delete;
    Free& operator = (const Free&) = delete;
    ~Free() = default;

    Free(unsigned int BlockSize);
    Free(Used& rUsed);

};

#endif 

// --- End of File ---
