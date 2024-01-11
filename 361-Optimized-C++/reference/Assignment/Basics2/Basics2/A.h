//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef A_H
#define A_H

// ----------------------------------------------------------------------
//
// Problem 1
//
// Related files:  A.h, B.h
//
// Rules: 
//     FIX class A to prevent the memory leak in the unit tests
//
//     1) Only modify class A
//     2) Do NOT modify class B in any way
//
// ----------------------------------------------------------------------

// -----------------------------------------------------
// REFACTOR class A - MODIFY this FILE
// -----------------------------------------------------

class A
{
public:
	A();
	~A();

	int getX();

private:
	int x;
};

#endif

// --- End of File ---
