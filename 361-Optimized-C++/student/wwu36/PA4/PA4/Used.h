//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef USED_H
#define USED_H

#include "Type.h"

class Free;

class Used
{
public:
   // ---------------------------------------------------------
   // Do not reorder, change or add data fields
   //     --> any changes to the data... 0 given to the assignment
   // You can add methods if you wish
   // ---------------------------------------------------------

    Used *pNext;              // next free Type
    Used *pPrev;              // prev free Type  
    uint16_t   mAllocSize;    // size (16 bit)
    Type       mType;         // Type type 
    bool       bAboveFree;    // Type above is free (T/F)

    Used() = default;
    Used(const Used&) = delete;
    Used &operator = (const Used&) = delete;
    ~Used() = default;
    
    Used(Free& rFree);

};

#endif 

// --- End of File ---

