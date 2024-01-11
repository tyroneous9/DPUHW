//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "B.h"

TEST(Test_B, TestConfig::ALL)
{
#if Test_B

	// Modifiy B.cpp to correct for error

	int val = B();
	CHECK(val == 4);

#endif
} TEST_END



// ---  End of File ---------------
