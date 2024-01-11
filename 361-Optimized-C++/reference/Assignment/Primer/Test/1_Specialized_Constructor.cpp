//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Specialized_Constructor, TestConfig::ALL)
{
#if Specialized_Constructor

	// Specialized Constructor
	Dog rex(5,7,9);

	CHECK(((TestDog &)rex).x == 5);
	CHECK(((TestDog &)rex).y == 7);
	CHECK(((TestDog &)rex).z == 9);

#endif
} TEST_END

// --- End of File ---
