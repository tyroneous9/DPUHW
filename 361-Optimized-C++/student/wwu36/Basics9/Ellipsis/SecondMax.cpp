//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <vector>
#include <algorithm>

#include "SecondMax.h"

int SecondMax(int count, ...)
{
    va_list args;
    va_start(args, count);

    int max1 = va_arg(args, int);
    int max2 = va_arg(args, int);

    if (max2 > max1)
        std::swap(max1, max2);

    for (int i = 2; i < count; i++)
    {
        int num = va_arg(args, int);

        if (num > max1)
        {
            max2 = max1;
            max1 = num;
        }
        else if (num > max2 && num < max1)
        {
            max2 = num;
        }
    }

    va_end(args);

    return max2;
}

// ---  End of File ---------------
