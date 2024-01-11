//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "SecondMax.h"

TEST(SecondMax_test_enable, TestConfig::ALL)
{
#if SecondMax_test_enable 

	int val;

	// Easy
	val = SecondMax(3, 13, 38, 4);
	CHECK(val == 13);

	// a little harder
	val = SecondMax(5, 6, 3, 8, 9, 7);
	CHECK(val == 8);

	val = SecondMax(10, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2);
	CHECK(val == 5);

	// hardest
	// remember its the second largest value, not the second value
	// So you need to remove redundants since there are two 5, so 4 is the second largest value
	val = SecondMax(10, 1, 2, 3, 4, 5, 2, 5, 4, 3, 2);
	CHECK(val == 4);

	val = SecondMax(10, 1, 2, 3, 8, 7, 8, 7, 8, 3, 2);
	CHECK(val == 7);

	val = SecondMax(15, 1, 2, 3, 8, 7, 9, 7, 8, 3, 2, 10, 6, 3, 2, 1);
	CHECK(val == 9);

#endif
} TEST_END

// ---  End of File ---------------
