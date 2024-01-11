//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "A.h"

TEST( Test_A, TestConfig::ALL)
{
#if Test_A	

	// Modifiy A.cpp to correct for error

	double val = A();
	CHECK(val == 4.2);

#endif
} TEST_END



// ---  End of File ---------------
