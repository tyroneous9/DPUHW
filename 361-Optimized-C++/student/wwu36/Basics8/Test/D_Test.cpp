//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "D.h"

TEST(Test_D, TestConfig::ALL)
{
#if Test_D

	// Fix D.h to have the correct behavior

	int val = 0;
	val = minD(42, 7, 68);
	CHECK(val == 7);

	const char *  const s0 = "CSC";
	const char *  const s1 = "461";
	const char *  const s2 = "Optimized C++";

	const char *s = 0;
	s = minD(s0, s1, s2);
	CHECK(strcmp(s, "461") == 0);

#endif
} TEST_END

// ---  End of File ---------------
