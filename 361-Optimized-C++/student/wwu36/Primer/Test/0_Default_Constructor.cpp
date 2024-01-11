//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Default_Constructor, TestConfig::ALL)
{
#if Default_Constructor

	// Default Constructor
	Dog rex;

	CHECK(((TestDog &)rex).x == 99);
	CHECK(((TestDog &)rex).y == 98);
	CHECK(((TestDog &)rex).z == 97);

#endif
} TEST_END

// --- End of File ---
