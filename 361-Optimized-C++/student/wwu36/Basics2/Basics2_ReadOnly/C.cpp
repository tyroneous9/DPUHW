//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//-----------------------------------------------------------------------------

#include "C.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

C::C()
	: x(33), y(44)
{
}

C::C(int valX, int valY)
	: x(valX), y(valY)
{
}

int C::getX()
{
	return this->x;
}

int C::getY()
{
	return this->y;
}

// --- End of File ---