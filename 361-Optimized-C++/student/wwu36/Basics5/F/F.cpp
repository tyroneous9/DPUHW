//----------------------------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "F.h"

// ----------------------------------------------------------------------
//
// F - Project
//
// Rules: fix the smal bug in the function, called findBitsInNibble
//        to output the correct number of '1' bits of any given number
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Function: returns the number of 1 bits in a the data
// ----------------------------------------------------------------------
int FindBitsInNibble(unsigned int data)
{
	int n(0);
	//int bitPattern[NUM_BITS] = { 0, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 3, 2, 3, 4 };
	int bitPattern[NUM_BITS] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };

	while (data > 0)
	{
		n += bitPattern[data & 0xF];
		data >>= 4;
	}
	return n;
}

// End of File