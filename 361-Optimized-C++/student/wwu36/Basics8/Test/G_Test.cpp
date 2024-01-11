//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "G.h"

TEST(Test_G, TestConfig::ALL)
{
#if Test_G

	// Modify G.h
	//
	// There should be two classes defined in this header
	//     Generalized Template class
	//     Partial Specialization class
	// 
	// Create a partial specializaton on S for second type is int
	//     In this partial specializaton, have the integer store 3x the input value

	// Do not change the code below is a no no -----------------------

	container< float, float >  container_floats;

	container_floats.setData0(5.0f);
	container_floats.setData1(10.0f);

	float fval;

	fval = container_floats.getData0();
	CHECK(fval == 5.0f);

	fval = container_floats.getData1();
	CHECK(fval == 10.0f);

	container< float, char >  container_floatchar;

	container_floatchar.setData0(77.0f);
	container_floatchar.setData1('b');

	char cval;

	fval = container_floatchar.getData0();
	CHECK(fval == 77.0f);

	cval = container_floatchar.getData1();
	CHECK(cval == 'b');


	container< float, int >  container_floatint;

	container_floatint.setData0(99.0f);
	container_floatint.setData1(11);

	int ival;

	fval = container_floatint.getData0();
	CHECK(fval == 99.0f);

	ival = container_floatint.getData1();
	CHECK(ival == 33);

#endif
} TEST_END

// ---  End of File ---------------
