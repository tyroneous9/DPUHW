//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "MiddlewareNative.h"
#include "Wrapper.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

int Vect2D_Native::s_const = 0x5;
int Vect2D_Native::s_id    = 0x55 ;
int Vect2D_Native::s_setx  = 0x155;
int Vect2D_Native::s_sety  = 0x255;
int Vect2D_Native::s_getx  = 0x355;
int Vect2D_Native::s_gety  = 0x455;
int Vect2D_Native::s_setid = 0x555;
int Vect2D_Native::s_getid = 0x655;

TEST(Private1, TestConfig::ALL)
{
#if Private1

	// Make sure the Native is working as advertised
	CHECK(sizeof(Vect2D_Native) == 12);
	CHECK(sizeof(GameVect) == 12);

	Vect2D_Native vNative;

	CHECK(Vect2D_Native::s_const == 6);
	CHECK(Vect2D_Native::s_id    == 0x55);
	CHECK(Vect2D_Native::s_setx  == 0x155);
	CHECK(Vect2D_Native::s_sety  == 0x255);
	CHECK(Vect2D_Native::s_getx  == 0x355);
	CHECK(Vect2D_Native::s_gety  == 0x455);
	CHECK(Vect2D_Native::s_setid == 0x555);
	CHECK(Vect2D_Native::s_getid == 0x655);
	CHECK(vNative.getX() == 22.0f);
	CHECK(vNative.getY() == 33.0f);

	vNative.setX(77);
	vNative.setY(88);
	vNative.setID(55);

	CHECK(Vect2D_Native::s_const == 6);
	CHECK(Vect2D_Native::s_id == 55);
	CHECK(Vect2D_Native::s_setx == 0x156);
	CHECK(Vect2D_Native::s_sety == 0x256);
	CHECK(Vect2D_Native::s_getx == 0x356);
	CHECK(Vect2D_Native::s_gety == 0x456);
	CHECK(Vect2D_Native::s_setid == 0x556);
	CHECK(Vect2D_Native::s_getid == 0x655);

	CHECK(vNative.getID() == 55);
	CHECK(vNative.getX() == 77.0f);
	CHECK(vNative.getY() == 88.0f);

	// Now check the wrapper class
	GameVect gVect;

	// Magic to test the base class (not good practice)
	Vect2D_Native *p = (Vect2D_Native *)&gVect;

	CHECK(Vect2D_Native::s_const == 7);
	CHECK(Vect2D_Native::s_id == 55);
	CHECK(Vect2D_Native::s_setx == 0x156);
	CHECK(Vect2D_Native::s_sety == 0x256);
	CHECK(Vect2D_Native::s_getx == 0x357);
	CHECK(Vect2D_Native::s_gety == 0x457);
	CHECK(Vect2D_Native::s_setid == 0x556);
	CHECK(Vect2D_Native::s_getid == 0x656);

	CHECK(p->getID() == 55);
	CHECK(p->getX() == 22.0f);
	CHECK(p->getY() == 33.0f);

	CHECK(Vect2D_Native::s_const == 7);
	CHECK(Vect2D_Native::s_id == 55);
	CHECK(Vect2D_Native::s_setx == 0x156);
	CHECK(Vect2D_Native::s_sety == 0x256);
	CHECK(Vect2D_Native::s_getx == 0x358);
	CHECK(Vect2D_Native::s_gety == 0x458);
	CHECK(Vect2D_Native::s_setid == 0x556);
	CHECK(Vect2D_Native::s_getid == 0x657);


	// Get it by the new methods
	float xVal;
	gVect.getX(xVal);

	CHECK(xVal == 22.0f);

	CHECK(Vect2D_Native::s_const == 7);
	CHECK(Vect2D_Native::s_id == 55);
	CHECK(Vect2D_Native::s_setx == 0x156);
	CHECK(Vect2D_Native::s_sety == 0x256);
	CHECK(Vect2D_Native::s_getx == 0x358);
	CHECK(Vect2D_Native::s_gety == 0x458);
	CHECK(Vect2D_Native::s_setid == 0x556);
	CHECK(Vect2D_Native::s_getid == 0x657);

	float yVal;
	gVect.getY(yVal);

	CHECK(yVal == 33.0f);

	CHECK(Vect2D_Native::s_const == 7);
	CHECK(Vect2D_Native::s_id == 55);
	CHECK(Vect2D_Native::s_setx == 0x156);
	CHECK(Vect2D_Native::s_sety == 0x256);
	CHECK(Vect2D_Native::s_getx == 0x358);
	CHECK(Vect2D_Native::s_gety == 0x458);
	CHECK(Vect2D_Native::s_setid == 0x556);
	CHECK(Vect2D_Native::s_getid == 0x657);

	// Set it by the new methods
	gVect.setX(66.0f);
	gVect.setY(77.0f);

	gVect.getX(xVal);
	gVect.getY(yVal);

	CHECK(xVal == 66.0f);
	CHECK(yVal == 77.0f);

	CHECK(Vect2D_Native::s_const == 7);
	CHECK(Vect2D_Native::s_id == 55);
	CHECK(Vect2D_Native::s_setx == 0x157);
	CHECK(Vect2D_Native::s_sety == 0x257);
	CHECK(Vect2D_Native::s_getx == 0x358);
	CHECK(Vect2D_Native::s_gety == 0x458);
	CHECK(Vect2D_Native::s_setid == 0x556);
	CHECK(Vect2D_Native::s_getid == 0x657);

// When you run the Basics2Wrapper.sln... 
// the following lines should generate errors

#ifdef WRAPPER_CHECK // make sure you get an error for each of the following statements

	int iVal;

	// 1)  Error
	gVect.getX(iVal);

	// 2) Error
	xVal = gVect.getX();

	// 3)  Error
	gVect.getY(iVal);

	// 4) Error
	yVal = gVect.getY();

	// 5) Error
	gVect.setID(0x33);

	// 6) Error
	iVal = gVect.getID();

	// 7)  Error
	gVect.x;

	// 8) Error
	gVect.y;

#endif
#endif
} TEST_END

// --- End of File ---
