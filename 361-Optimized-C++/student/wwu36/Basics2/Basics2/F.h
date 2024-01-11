//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef F_H
#define F_H

#include "E.h"

// ----------------------------------------------------------------------
//
// Problem 3
//
// Related files:  E.h, F.h, G.h, H.h
//
// Rules: 
//     Modify the classes to pass tests
//     The class should be in a diamond inheritance pattern
//     Only one variable in (H: a,b,c,d ) no duplicates or replicas
//
//     1) Do NOT modify class E in any way
//     2) Do NOT modify class H in any way
//     3) Refactor class F to pass tests
//     4) Refactor class G to pass tests
//
// ----------------------------------------------------------------------

// -----------------------------------------------------
// REFACTOR class F - MODIFY this FILE
// -----------------------------------------------------

class F : virtual public E
{
public:
	F();

	void foo();

	int b;
};

#endif

// --- End of File ---
