//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef MIDDLEWARE_NATIVE_H
#define MIDDLEWARE_NATIVE_H

// ----------------------------------------------------------------------
//
// Problem 5
//
// Related files:  MiddlewareNative.h, Wrapper.h
//
// Rules: 
//     For this problem, you are wrapping a poor interface provided by a middleware vendors
//
//     This is a mockup of a middleware class
//         Too many functions and/or incorrect were provided to the End User
//
// The GameVect class needs to derive privately from Vect2D_Native
//
// Requirements:
//
//     1) variables:  x, y should be private
//     2) prevent methods setID() and getID() from being called
//     3) Rework getX() and getY() to take float references
//     4) prevent the original getX() and getY() from being called
//     5) allow setX() and setY() to be called as is.
//
// Run Basics2Debug.sln - should generate no errors and pass the tests
// Run Basics2Wrapper.sln to make sure your code is producing the correct errors
//
// Rules:
//
//     1) Do NOT modify class Vect2D_Native
//     2) GameVect class in Wrapper.h must derive privately from Vect2D_Native
//     3) Refactor GameVect class to meet the above requirements
//
// ----------------------------------------------------------------------

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

class Vect2D_Native
{
public:
	Vect2D_Native();

	virtual void setX(float val) final;
	virtual void setY(float val) final;

	float getX();
	float getY();

	void setID(int val);
	int getID();

	// Data:
	//       - Yes its public (that's the problem)
	float x;
	float y;

	// Ignore for testing purposes:
	static int s_const;
	static int s_id;
	static int s_setx;
	static int s_sety;
	static int s_getx;
	static int s_gety;
	static int s_setid;
	static int s_getid;
};

#endif

// --- End of File ---
