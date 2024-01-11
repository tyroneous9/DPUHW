//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "C_Interface.h"

TEST(Test_C, TestConfig::ALL)
{
#if Test_C

	// Modifiy C.cpp to correct for error

	ReturnType val_1;
	ReturnType val_2;
	ReturnType val_3;
	ReturnType val_4;
	ReturnType val_5;
	ReturnType val_6;
	ReturnType val_7;

	C(val_1, val_2, val_3, val_4, val_5, val_6, val_7);

	// call min with 3 ints:  42, 7, 68
	// example: val = blahblah(42,7,68);
	CHECK(val_1 == TEMPLATE_3_ARG);

	// call min with 2 doubles by argument deduction:  42.0, 7.0
	CHECK(val_2 == TEMPLATE_2_ARG);

	// call min with 2 characters by argument deduction: 'a', 'b'
	CHECK(val_3 == TEMPLATE_2_ARG);

	// call min with 2 int:  42, 7
	CHECK(val_4 == NON_TEMPLATE_INT_ARG);

	// call min with 2 int by argument deduction:  42, 7
	CHECK(val_5 == TEMPLATE_2_ARG);

	// call min with 2 double no argument deduction:  42, 7
	CHECK(val_6 == TEMPLATE_2_ARG);

	// call min with 2 ints:  42, 'a'
	CHECK(val_7 == NON_TEMPLATE_INT_ARG);

#endif
} TEST_END

// ---  End of File ---------------
