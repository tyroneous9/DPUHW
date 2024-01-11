//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "B.h"

int B() // Templates arguments
{
	int val = 0;

	// Fix this template call without a cast
	// Specify the type or qualify explicity the type of T
	// Only change the next line

	 val = minB<int, double, int>(5, 4.2);

	return val;
}

// ---  End of File ---------------
