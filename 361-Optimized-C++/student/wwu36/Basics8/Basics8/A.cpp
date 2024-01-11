//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "A.h"

double A()  // Argument Deduction
{
	double val = 0.0f;

	// Fix this template call without a cast
	// Specify the type or qualify explicity the type of T
	// Only change this call line below:

	val = minA<double>(5, 4.2); 

	return val;
}

// ---  End of File ---------------
