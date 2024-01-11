//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef C_H
#define C_H

// ----------------------------------------------------------------------
//
// Problem 2
//
// Related files:  C.h, D.h
//
// Rules: 
//     FIX class D to pass the unit tests
//
//     1) Do NOT modify class C in any way
//     2) Only modify Class D's constructor to pass the class
//
// ----------------------------------------------------------------------

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

class C
{
public:
	C();
	C(int valX, int valY);

	int getX();
	int getY();

private:
	int x;
	int y;
};

#endif

// --- End of File ---
